/**
  @file
  @author Stefan Frings
*/

#include "httplistener.h"
#include "httpconnectionhandler.h"
#include "httpconnectionhandlerpool.h"
#include <QCoreApplication>

HttpListener::HttpListener(QSettings* settings, HttpRequestHandler* requestHandler, QObject* parent)
      : QTcpServer(parent), pool(settings, requestHandler) {
      Q_ASSERT(settings != 0);
      this->settings = settings;
      // Start listening
      int port = settings->value("port").toInt();
      listen(QHostAddress::Any, port);
      if (!isListening()) {
            qCritical("HttpListener: Cannot bind on port %i: %s", port, qPrintable(errorString()));
            }
      else {
            qDebug("HttpListener: Listening on port %i", port);
            }
      }

HttpListener::~HttpListener() {
      close();
      qDebug("HttpListener: closed");
      }


void HttpListener::incomingConnection(qintptr socketDescriptor)
      {
      HttpConnectionHandler* freeHandler = pool.getConnectionHandler();

      // Let the handler process the new connection.
      if (freeHandler) {
            // The descriptor is passed via signal/slot because the handler lives in another
            // thread and cannot open the socket when called by another thread.
            connect(this, SIGNAL(handleConnection(void*)), freeHandler, SLOT(handleConnection(void*)));
            emit handleConnection((void*)socketDescriptor);
            disconnect(this, SIGNAL(handleConnection(void*)), freeHandler, SLOT(handleConnection(void*)));
            }
      else {
            // Reject the connection
            qDebug("HttpListener: Too many connections");
            QTcpSocket* socket = new QTcpSocket(this);
            socket->setSocketDescriptor(socketDescriptor);
            connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
            socket->write("HTTP/1.1 503 too many connections\r\nConnection: close\r\n\r\nToo many connections\r\n");
            socket->disconnectFromHost();
            }
      }
