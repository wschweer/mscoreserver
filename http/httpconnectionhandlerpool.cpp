#include "httpconnectionhandlerpool.h"

//---------------------------------------------------------
//   HttpConnectionHandlerPool
//---------------------------------------------------------

HttpConnectionHandlerPool::HttpConnectionHandlerPool(QSettings* s, HttpRequestHandler* rh)
      : QObject() {
      settings       = s;
      requestHandler = rh;
      cleanupTimer.start(settings->value("cleanupInterval", 1000).toInt());
      connect(&cleanupTimer, SIGNAL(timeout()), SLOT(cleanup()));
      }

//---------------------------------------------------------
//   ~HttpConnectionHandlerPool
//---------------------------------------------------------

HttpConnectionHandlerPool::~HttpConnectionHandlerPool() {
      qDeleteAll(pool);
      pool.clear();
      }

//---------------------------------------------------------
//   getConnectionHandler
//---------------------------------------------------------

HttpConnectionHandler* HttpConnectionHandlerPool::getConnectionHandler()
      {
      HttpConnectionHandler* freeHandler = 0;
      freeHandler = new HttpConnectionHandler(settings, requestHandler, this);
      freeHandler->setBusy();

#if 0
      printf("getHandler %d\n", pool.size());

      mutex.lock();
      foreach (HttpConnectionHandler* handler, pool) {
            if (!handler->isBusy()) {
                  freeHandler = handler;
                  freeHandler->setBusy();
                  break;
                  }
            }
      if (!freeHandler) {
            int maxConnectionHandlers = settings->value("maxThreads", 100).toInt();
            if (pool.count() < maxConnectionHandlers) {
                  freeHandler = new HttpConnectionHandler(settings, requestHandler, this);
                  freeHandler->setBusy();
                  pool.append(freeHandler);
                  }
            }
      mutex.unlock();
#endif
      return freeHandler;
      }

//---------------------------------------------------------
//   freeHandler
//---------------------------------------------------------

void HttpConnectionHandlerPool::freeHandler(HttpConnectionHandler* h)
      {
      printf("free handler %d\n", pool.size());
      connect(h, SIGNAL(finished()), h, SLOT(deleteLater()));
      h->quit();
#if 0
      mutex.lock();
      h->getSocket()->abort();
      pool.append(pool.takeAt(pool.indexOf(h)));
      h->setBusy(false);
      mutex.unlock();
#endif
      }

//---------------------------------------------------------
//   cleanup
//---------------------------------------------------------

void HttpConnectionHandlerPool::cleanup() {
      int maxIdleHandlers = settings->value("minThreads", 1).toInt();
      int idleCounter     = 0;

      mutex.lock();
      foreach(HttpConnectionHandler * handler, pool) {
            if (handler->isBusy())
                  continue;
            if (++idleCounter > maxIdleHandlers) {
                  pool.removeOne(handler);
                  qDebug("HttpConnectionHandlerPool: Removed connection handler (%p), pool size is now %i", handler, pool.size());
                  connect(handler, SIGNAL(finished()), handler, SLOT(deleteLater()));
                  handler->quit();
                  break; // remove only one handler in each interval
                  }
            }
      mutex.unlock();
      }

