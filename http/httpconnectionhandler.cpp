/**
  @file
  @author Stefan Frings
*/

#include "httpconnectionhandler.h"
#include "httpresponse.h"
#include <QTimer>
#include <QCoreApplication>
#include "httpconnectionhandlerpool.h"

HttpConnectionHandler::HttpConnectionHandler(QSettings* s, HttpRequestHandler* rh,
            HttpConnectionHandlerPool* p) : QThread()
      {
      settings       = s;
      requestHandler = rh;
      pool           = p;
      currentRequest = 0;
      busy           = false;

      // execute signals in my own thread
      moveToThread(this);
      socket.moveToThread(this);
      readTimer.moveToThread(this);
      connect(&socket, SIGNAL(readyRead()), SLOT(read()));
      connect(&socket, SIGNAL(disconnected()), SLOT(disconnected()));
      connect(&readTimer, SIGNAL(timeout()), SLOT(readTimeout()));
      readTimer.setSingleShot(true);
      start();
      }


HttpConnectionHandler::~HttpConnectionHandler() {
      qDebug("HttpConnectionHandler (%p): destroyed", this);
      }

void HttpConnectionHandler::run()
      {
      exec();
      // Change to the main thread, otherwise deleteLater() would not work
      moveToThread(QCoreApplication::instance()->thread());
      }

//---------------------------------------------------------
//   handleConnection
//---------------------------------------------------------

void HttpConnectionHandler::handleConnection(void* descr)
      {
      qintptr socketDescriptor = (qintptr)descr;

      Q_ASSERT(socket.isOpen() == false); // if not, then the handler is already busy
      if (!socket.setSocketDescriptor(socketDescriptor)) {
            qCritical("HttpConnectionHandler (%p): cannot initialize socket: %s", this, qPrintable(socket.errorString()));
            return;
            }
      // Start timer for read timeout
      int readTimeout = settings->value("readTimeout", 3000).toInt();
      readTimer.start(readTimeout);
      delete currentRequest;
      currentRequest = 0;
      }


void HttpConnectionHandler::readTimeout()
      {
      socket.write("HTTP/1.1 408 request timeout\r\nConnection: close\r\n\r\n408 request timeout\r\n");
      socket.disconnectFromHost();
      delete currentRequest;
      currentRequest = 0;
      }

//---------------------------------------------------------
//   disconnected
//---------------------------------------------------------

void HttpConnectionHandler::disconnected() {
      socket.close();
      readTimer.stop();
      pool->freeHandler(this);
      }

//---------------------------------------------------------
//   read
//---------------------------------------------------------

void HttpConnectionHandler::read()
      {
      // Create new HttpRequest object if necessary
      if (!currentRequest)
            currentRequest = new HttpRequest(settings);

      // Collect data for the request object
      while (socket.bytesAvailable() && currentRequest->getStatus() != HttpRequest::complete
                  && currentRequest->getStatus() != HttpRequest::abort) {
            currentRequest->readFromSocket(socket);
            if (currentRequest->getStatus() == HttpRequest::waitForBody) {
                  // Restart timer for read timeout, otherwise it would
                  // expire during large file uploads.
                  int readTimeout = settings->value("readTimeout", 3000).toInt();
                  readTimer.start(readTimeout);
                  }
            }

      if (currentRequest->getStatus() == HttpRequest::abort) {

            // If the request is aborted, return error message and close the connection

            socket.write("HTTP/1.1 413 entity too large\r\nConnection: close\r\n\r\n413 Entity too large\r\n");
            socket.disconnectFromHost();
            }
      else if (currentRequest->getStatus() == HttpRequest::complete) {

            // If the request is complete, let the request mapper dispatch it

            readTimer.stop();
            qDebug("HttpConnectionHandler (%p): received request", this);
            HttpResponse response(&socket);
            bool closeConnection = QString::compare(currentRequest->getHeader("Connection"), "close", Qt::CaseInsensitive) == 0;
            requestHandler->service(*currentRequest, response);

            // Finalize sending the response if not already done
            if (!response.hasSentLastPart())
                  response.write(QByteArray(), true);

            // Close the connection after delivering the response, if requested
            if (closeConnection)
                  socket.disconnectFromHost();
            else {
                  // Start timer for next request
                  int readTimeout = settings->value("readTimeout", 3000).toInt();
                  readTimer.start(readTimeout);
                  }
            }
      delete currentRequest;
      currentRequest = 0;
      }
