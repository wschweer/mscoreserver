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

#include "libmscore/score.h"
#include "libmscore/xml.h"
#include "libmscore/page.h"

#include "mscorecontroller.h"

MScoreController::MScoreController(QObject* parent)
      {
      }

MScoreController::~MScoreController()
      {
      }

//---------------------------------------------------------
//   processPng
//---------------------------------------------------------

static void processPng(HttpResponse& response, Score* score)
      {
      qreal convDpi = 100.0;
      score->setPrinting(true);

      QImage::Format f = QImage::Format_ARGB32_Premultiplied;

      const QList<Page*>& pl = score->pages();

      Page* page = pl.at(0);

      QRectF r = page->abbox();
      int w = lrint(r.width()  * convDpi / MScore::DPI);
      int h = lrint(r.height() * convDpi / MScore::DPI);

      QImage printer(w, h, f);
      printer.setDotsPerMeterX(lrint((convDpi * 1000) / INCH));
      printer.setDotsPerMeterY(lrint((convDpi * 1000) / INCH));

      printer.fill(0xffffffff);

      double mag = convDpi / MScore::DPI;
      QPainter p(&printer);

      p.setRenderHint(QPainter::Antialiasing, true);
      p.setRenderHint(QPainter::TextAntialiasing, true);
      p.scale(mag, mag);

      foreach(const Element* e, page->elements()) {
            if (!e->visible())
                  continue;
            QPointF pos(e->pagePos());
            p.translate(pos);
            e->draw(&p);
            p.translate(-pos);
            }
      score->setPrinting(false);
      QByteArray ba;
      QBuffer buffer(&ba);
      buffer.open(QIODevice::WriteOnly);
      printer.save(&buffer, "PNG");
      response.setHeader("Content-Type", "image/png");
      response.write(ba, true);
      }

//---------------------------------------------------------
//   processJpeg
//---------------------------------------------------------

static void processJpeg(HttpResponse& response, Score* score)
      {
      qreal convDpi = 100.0;
      score->setPrinting(true);

      QImage::Format f = QImage::Format_ARGB32_Premultiplied;

      const QList<Page*>& pl = score->pages();

      Page* page = pl.at(0);

      QRectF r = page->abbox();
      int w = lrint(r.width()  * convDpi / MScore::DPI);
      int h = lrint(r.height() * convDpi / MScore::DPI);

      QImage printer(w, h, f);
      printer.setDotsPerMeterX(lrint((convDpi * 1000) / INCH));
      printer.setDotsPerMeterY(lrint((convDpi * 1000) / INCH));

      printer.fill(0xffffffff);

      double mag = convDpi / MScore::DPI;
      QPainter p(&printer);

      p.setRenderHint(QPainter::Antialiasing, true);
      p.setRenderHint(QPainter::TextAntialiasing, true);
      p.scale(mag, mag);

      foreach(const Element* e, page->elements()) {
            if (!e->visible())
                  continue;
            QPointF pos(e->pagePos());
            p.translate(pos);
            e->draw(&p);
            p.translate(-pos);
            }
      score->setPrinting(false);
      QByteArray ba;
      QBuffer buffer(&ba);
      buffer.open(QIODevice::WriteOnly);
      if (!printer.save(&buffer, "JPEG"))
            printf("   export failed\n");
      response.setHeader("Content-Type", "image/jpeg");
      response.write(ba, true);
      }

//---------------------------------------------------------
//   processGif
//---------------------------------------------------------

static void processGif(HttpResponse& response, Score* score)
      {
      printf("process gif...\n");
      qreal convDpi = 100.0;
      score->setPrinting(true);

      QImage::Format f = QImage::Format_ARGB32_Premultiplied;

      const QList<Page*>& pl = score->pages();

      Page* page = pl.at(0);

      QRectF r = page->abbox();
      int w = lrint(r.width()  * convDpi / MScore::DPI);
      int h = lrint(r.height() * convDpi / MScore::DPI);

      QImage printer(w, h, f);
      printer.setDotsPerMeterX(lrint((convDpi * 1000) / INCH));
      printer.setDotsPerMeterY(lrint((convDpi * 1000) / INCH));

      printer.fill(0xffffffff);

      double mag = convDpi / MScore::DPI;
      QPainter p(&printer);

      p.setRenderHint(QPainter::Antialiasing, true);
      p.setRenderHint(QPainter::TextAntialiasing, true);
      p.scale(mag, mag);

      foreach(const Element* e, page->elements()) {
            if (!e->visible())
                  continue;
            QPointF pos(e->pagePos());
            p.translate(pos);
            e->draw(&p);
            p.translate(-pos);
            }
      score->setPrinting(false);
      QByteArray ba;
      QBuffer buffer(&ba);
      buffer.open(QIODevice::WriteOnly);
      if (!printer.save(&buffer, "GIF"))
            printf("   export failed\n");
      response.setHeader("Content-Type", "image/gif");
      printf("   respond %d\n", ba.size());
      response.write(ba, true);
      }

//---------------------------------------------------------
//   service
//---------------------------------------------------------

void MScoreController::service(HttpRequest& request, HttpResponse& response)
      {
      QByteArray path = request.getPath();
      printf("MScoreController::service: <%s>\n", qPrintable(path));

      QByteArray method = request.getMethod();
      if (method != "POST") {
            printf("bad method <%s>\n", qPrintable(method));
            return;
            }

      QTemporaryFile* f = request.getUploadedFile("score");
      if (!f)
            printf(" no upload file\n");
      else {
            QByteArray data = f->readAll();

            Score* score = new Score;
            XmlReader xr(data);
            score->read1(xr, true);

            QByteArray s = request.getParameter("size");
            if (!s.isEmpty()) {
                  int size = s.toInt();
                  if (size < 10)
                        size = 10;
                  else if (size > 400)
                        size = 400;
                  qreal spatium = score->spatium();
                  spatium = (spatium * size) / 100.0;
                  score->setSpatium(spatium);
                  }

            score->doLayout();
            //
            // process score
            //
            QByteArray format = request.getParameter("format");
            if (format == "png")
                  processPng(response, score);
            else if (format == "jpeg")
                  processGif(response, score);
            else if (format == "gif")
                  processGif(response, score);
            else {
                  printf("bad format <%s>\n", qPrintable(format));
                  return;
                  }
            delete score;
            }
      }
