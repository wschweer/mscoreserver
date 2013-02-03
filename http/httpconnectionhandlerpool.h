#ifndef HTTPCONNECTIONHANDLERPOOL_H
#define HTTPCONNECTIONHANDLERPOOL_H

#include <QList>
#include <QTimer>
#include <QObject>
#include <QMutex>
#include "httpconnectionhandler.h"

/**
  Pool of http connection handlers. Connection handlers are created on demand and idle
  handlers are cleaned up in regular time intervals.
  <p>
  Example for the required configuration settings:
  <code><pre>
  minThreads=1
  maxThreads=100
  cleanupInterval=1000
  maxRequestSize=16000
  maxMultiPartSize=1000000
  </pre></code>
  The pool is empty initially and grows with the number of concurrent
  connections. A timer removes one idle connection handler at each
  interval, but a it leaves some spare handlers in memory to improve
  performance.
  @see HttpConnectionHandler for description of config settings readTimeout
  @see HttpRequest for description of config settings maxRequestSize and maxMultiPartSize
*/

//---------------------------------------------------------
//   HttpConnectionHandlerPool
//---------------------------------------------------------

class HttpConnectionHandlerPool : public QObject {
            Q_OBJECT
            Q_DISABLE_COPY(HttpConnectionHandlerPool)

            QSettings* settings;
            HttpRequestHandler* requestHandler;
            QList<HttpConnectionHandler*> pool;

            QTimer cleanupTimer;

            QMutex mutex;

      private slots:
            void cleanup();   /** Received from the clean-up timer.  */

      public:
            /**
              Constructor.
              @param settings Configuration settings for the HTTP server. Must not be 0.
              @param requestHandler The handler that will process each received HTTP request.
              @warning The requestMapper gets deleted by the destructor of this pool
            */
            HttpConnectionHandlerPool(QSettings* settings, HttpRequestHandler* requestHandler);

            virtual ~HttpConnectionHandlerPool();
            HttpConnectionHandler* getConnectionHandler();
            void freeHandler(HttpConnectionHandler*);
      };

#endif // HTTPCONNECTIONHANDLERPOOL_H
