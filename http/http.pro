QT       = core network
TARGET   = http
TEMPLATE = lib
CONFIG  += staticlib debug

CONFIG(debug, debug|release) {
      DEFINES += SUPERVERBOSE
      }

QMAKE_CXXFLAGS += -std=c++0x -O2

INCLUDEPATH += ../utils
INCLUDEPATH += ..

SOURCES = dualfilelogger.cpp filelogger.cpp \
      httpconnectionhandler.cpp httpconnectionhandlerpool.cpp \
      httpcookie.cpp httplistener.cpp httprequest.cpp \
      httprequesthandler.cpp \
      httpresponse.cpp \
      httpsession.cpp \
      httpsessionstore.cpp \
      logger.cpp \
      logmessage.cpp \
      qtservice.cpp \
      qtservice_unix.cpp \
      qtunixserversocket.cpp \
      qtunixsocket.cpp \
      staticfilecontroller.cpp

HEADERS =  dualfilelogger.h \
      filelogger.h \
      httpconnectionhandler.h \
      httpconnectionhandlerpool.h \
      httpcookie.h \
      httplistener.h \
      httprequest.h \
      httprequesthandler.h \
      httpresponse.h \
      httpsession.h \
      httpsessionstore.h \
      logger.h \
      logmessage.h \
      qtservice.h \
      qtservice_p.h \
      qtunixserversocket.h \
      qtunixsocket.h \
      staticfilecontroller.h

