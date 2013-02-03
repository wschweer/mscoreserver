//=============================================================================
//  MuseScore
//  Music Composition & Notation
//
//  Copyright (C) 2004-2012 Werner Schweer and others
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2
//  as published by the Free Software Foundation and appearing in
//  the file LICENSE.GPL
//=============================================================================

#ifndef __ALLQT_H__
#define __ALLQT_H__

#include <stdio.h>
#include <limits.h>
#include <map>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

#include <QtGui/QtGui>
#include <QtCore/QModelIndex>

#include <QtXml/QtXml>
#include <QtXmlPatterns/QXmlSchema>
#include <QtXmlPatterns/QXmlSchemaValidator>

#include <QtCore/QPointF>
#include <QtCore/QVariant>
#include <QtCore/QMap>
#include <QtCore/QDateTime>
#include <QtCore/QtGlobal>
#include <QtCore/QtDebug>
#include <QtCore/QSharedData>
#include <QtCore/QSharedDataPointer>

#include <QtCore/QAtomicInt>
#include <QtGui/QStaticText>

#include <QtGui/QPainterPath>
#include <QtGui/QBitmap>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QKeyEvent>

#include <QtGui/QFontDatabase>
#include <QtCore/QProcess>
#include <QtGui/QDesktopServices>
#include <QtGui/QTextDocument>
#include <QtGui/QTextDocumentFragment>
#include <QtGui/QTextCursor>
#include <QtGui/QAbstractTextDocumentLayout>
#include <QtGui/QTextBlock>
#include <QtGui/QTextList>
#include <QtGui/QTextFrameFormat>
#include <QtGui/QClipboard>

#if QT_VERSION >= 0x050000
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QItemDelegate>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWhatsThis>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QFileDialog>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QtWidgets/QColorDialog>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QAction>
#include <QtWidgets/QActionGroup>
#include <QtWidgets/QLayout>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QToolTip>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWizard>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSplashScreen>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QStylePainter>
#include <QtWidgets/QStyleOptionButton>
#include <QtWidgets/QStyleFactory>
#include <QtWidgets/QFileSystemModel>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QUndoGroup>
#include <QtWidgets/QUndoStack>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QLabel>
#include <QtWidgets/QFocusFrame>
#include <QtWidgets/QMouseEventTransition>
#include <QtWidgets/QCommonStyle>
#include <QtWidgets/QMdiSubWindow>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QtDeclarative/QDeclarativeListProperty>

#else

#include <QtGui/QDateTimeEdit>
#include <QtGui/QInputDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QSpinBox>
#include <QtGui/QScrollArea>
#include <QtGui/QScrollBar>
#include <QtGui/QToolBar>
#include <QtGui/QWhatsThis>
#include <QtGui/QTreeWidget>
#include <QtGui/QFileDialog>
#include <QtGui/QPrintDialog>
#include <QtGui/QColorDialog>
#include <QtGui/QDockWidget>
#include <QtGui/QStackedWidget>
#include <QtGui/QStackedLayout>
#include <QtGui/QListWidget>
#include <QtGui/QMessageBox>
#include <QtGui/QPrinter>
#include <QtGui/QComboBox>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSplitter>
#include <QtGui/QAction>
#include <QtGui/QActionGroup>
#include <QtGui/QLayout>
#include <QtGui/QBoxLayout>
#include <QtGui/QToolTip>
#include <QtGui/QToolBox>
#include <QtGui/QToolButton>
#include <QtGui/QPushButton>
#include <QtGui/QWizard>
#include <QtGui/QGroupBox>
#include <QtGui/QDial>
#include <QtGui/QTextEdit>
#include <QtGui/QLineEdit>
#include <QtGui/QCheckBox>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QProgressBar>
#include <QtGui/QRadioButton>
#include <QtGui/QSplashScreen>
#include <QtGui/QFontComboBox>
#include <QtGui/QApplication>
#include <QtGui/QStatusBar>
#include <QtGui/QStylePainter>
#include <QtGui/QStyleOptionButton>
#include <QtGui/QStyleFactory>
#include <QtGui/QFileSystemModel>
#include <QtGui/QHeaderView>
#include <QtGui/QUndoGroup>
#include <QtGui/QUndoStack>
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>
#include <QtGui/QLabel>
#include <QtGui/QFocusFrame>
#include <QtGui/QMouseEventTransition>
#include <QtGui/QCommonStyle>
#include <QtGui/QMdiSubWindow>
#include <QtGui/QGraphicsSceneMouseEvent>
#endif

#include <QtSvg/QSvgRenderer>
#include <QtSvg/QSvgGenerator>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkCookieJar>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QUdpSocket>

#include <QtNetwork/QHttpPart>
#include <QtNetwork/QHttpMultiPart>

#endif

