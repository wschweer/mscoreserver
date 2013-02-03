//=============================================================================
//  MuseScore
//  Music Composition & Notation
//  $Id:$
//
//  Copyright (C) 2013 Werner Schweer and others
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2
//  as published by the Free Software Foundation and appearing in
//  the file LICENSE.GPL
//=============================================================================

#include <stdio.h>
#include "libmscore/mscore.h"
#include "config.h"
#include "dualfilelogger.h"
#include "httplistener.h"
#include "mscorecontroller.h"

QString revision;

//---------------------------------------------------------
//   main
//---------------------------------------------------------

int main(int argc, char* argv[])
      {
      QGuiApplication _app(argc, argv);
      QGuiApplication* app = &_app;

      MScore::PDPI = 300; // view.logicalDpiX();
      MScore::DPI  = MScore::PDPI;        // logical drawing resolution
      MScore::DPMM = MScore::DPI / INCH;  // dots/mm
      MScore::init();

      app->setApplicationName("MuseScoreServer");
      app->setOrganizationName("MuseScore");

      QString configFileName = QDir::homePath() + "/mscoreserver/mscoreserver.ini";

      // Configure logging into files
      QSettings* mainLogSettings = new QSettings(configFileName, QSettings::IniFormat, app);
      mainLogSettings->beginGroup("mainLogFile");
      QSettings* debugLogSettings = new QSettings(configFileName, QSettings::IniFormat,app);
      debugLogSettings->beginGroup("debugLogFile");
      Logger* logger = new DualFileLogger(mainLogSettings, debugLogSettings, 10000, app);
      logger->installMsgHandler();

      // Configure session store
      QSettings* sessionSettings = new QSettings(configFileName,QSettings::IniFormat,app);
      sessionSettings->beginGroup("sessions");
//      Static::sessionStore = new HttpSessionStore(sessionSettings,app);

      QSettings* listenerSettings = new QSettings(configFileName,QSettings::IniFormat,app);
      listenerSettings->beginGroup("listener");
      new HttpListener(listenerSettings, new MScoreController(app), app);

      return app->exec();
      }

