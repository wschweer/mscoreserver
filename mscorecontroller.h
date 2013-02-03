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

#ifndef __MSCORECONTROLLER_H__
#define __MSCORECONTROLLER_H__

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

//---------------------------------------------------------
//   MScoreController
//---------------------------------------------------------

class MScoreController : public HttpRequestHandler
      {
      Q_OBJECT
      Q_DISABLE_COPY(MScoreController);

   public:
      MScoreController(QObject* parent);
      ~MScoreController();
      void service(HttpRequest& request, HttpResponse& response);
      };

#endif

