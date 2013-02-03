/**
  @file
  @author Stefan Frings
*/

#ifndef HTTPCONNECTIONHANDLER_H
#define HTTPCONNECTIONHANDLER_H

#include <QTcpSocket>
#include <QSettings>
#include <QTimer>
#include <QThread>
#include "httprequest.h"
#include "httprequesthandler.h"

/**
  The connection handler accepts incoming connections and dispatches incoming requests to to a
  request mapper. Since HTTP clients can send multiple requests before waiting for the response,
  the incoming requests are queued and processed one after the other.
  <p>
  Example for the required configuration settings:
  <code><pre>
  readTimeout=60000
  maxRequestSize=16000
  maxMultiPartSize=1000000
  </pre></code>
  <p>
  The readTimeout value defines the maximum time to wait for a complete HTTP request.
  @see HttpRequest for description of config settings maxRequestSize and maxMultiPartSize
*/

class HttpConnectionHandlerPool;

//---------------------------------------------------------
//   HttpConnectionHandler
//---------------------------------------------------------

class HttpConnectionHandler : public QThread {
            Q_OBJECT
            Q_DISABLE_COPY(HttpConnectionHandler)

            QSettings* settings;

            QTcpSocket socket;
            QTimer readTimer;
            HttpRequest* currentRequest;
            HttpRequestHandler* requestHandler;
            HttpConnectionHandlerPool* pool;
            void run();
            bool busy;  /** This shows the busy-state from a very early time */

      private slots:
            void readTimeout();     /** Received from the socket when a read-timeout occured */
            void read();            /** Received from the socket when incoming data can be read */
            void disconnected();    /** Received from the socket when a connection has been closed */

      public slots:
            /**
            Received from from the listener, when the handler shall start processing a new connection.
            @param socketDescriptor references the accepted connection.
            */
            void handleConnection(void* socketDescriptor);

      public:
            HttpConnectionHandler(QSettings*, HttpRequestHandler*, HttpConnectionHandlerPool*);
            virtual ~HttpConnectionHandler();
            bool isBusy()                 {
                  return busy;
                  }
            void setBusy(bool val = true) {
                  busy = val;
                  }
            QTcpSocket* getSocket() {
                  return &socket;
                  }
      };

#endif // HTTPCONNECTIONHANDLER_H
