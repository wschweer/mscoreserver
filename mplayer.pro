# Add more folders to ship with the application, here
folder_01.source = qml
folder_01.target = .
folder_02.source = js
folder_02.target = .
folder_03.source = demos
folder_03.target = .
DEPLOYMENTFOLDERS = folder_01 folder_02 folder_03

# deployment.files=mplayer.qml
deployment.path=/assets

#CONFIG += debug
INSTALLS += deployment


#version.target = buildNumber.h
#version.commands = bash ${QMAKE_VAR_PRO_FILE_PWD_}/incBuild
#QMAKE_EXTRA_TARGETS += version

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH = /assets

symbian:TARGET.UID3 = 0xE1F8D112

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
CONFIG += mobility
MOBILITY += systeminfo

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
# CONFIG += qdeclarative-boostable

# Add dependency to Symbian components
# CONFIG += qt-components                     c

CONFIG += precompiled_header
PRECOMPILED_HEADER = all.h

QT += xml declarative network
LIBS += -lOpenSLES

QMAKE_CXXFLAGS += -include all.h -fsigned-char -fno-rtti -ffast-math

RESOURCES += mscoreplay.qrc

SOURCES += main.cpp                       \
      downloadmanager.cpp                 \
      customnetworkmanagerfactory.cpp     \
      scoreview.cpp                       \
      seq.cpp                             \
      androidaudio.cpp                    \
      droptarget.cpp                      \
      libmscore/accidental.cpp            \
      libmscore/arpeggio.cpp              \
      libmscore/articulation.cpp          \
      libmscore/audio.cpp                 \
      libmscore/barline.cpp               \
      libmscore/beam.cpp                  \
      libmscore/bend.cpp                  \
      libmscore/box.cpp                   \
      libmscore/bracket.cpp               \
      libmscore/breath.cpp                \
      libmscore/bsp.cpp                   \
      libmscore/check.cpp                 \
      libmscore/chord.cpp                 \
      libmscore/chordline.cpp             \
      libmscore/chordlist.cpp             \
      libmscore/chordrest.cpp             \
      libmscore/clef.cpp                  \
      libmscore/cleflist.cpp              \
      libmscore/cmd.cpp                   \
      libmscore/cursor.cpp                \
      libmscore/drumset.cpp               \
      libmscore/dsp.cpp                   \
      libmscore/duration.cpp              \
      libmscore/durationtype.cpp          \
      libmscore/dynamic.cpp               \
      libmscore/edit.cpp                  \
      libmscore/element.cpp               \
      libmscore/elementlayout.cpp         \
      libmscore/elementmap.cpp            \
      libmscore/event.cpp                 \
      libmscore/excerpt.cpp               \
      libmscore/exportmidi.cpp            \
      libmscore/fifo.cpp                  \
      libmscore/figuredbass.cpp           \
      libmscore/fingering.cpp             \
      libmscore/fraction.cpp              \
      libmscore/fret.cpp                  \
      libmscore/glissando.cpp             \
      libmscore/hairpin.cpp               \
      libmscore/harmony.cpp               \
      libmscore/hook.cpp                  \
      libmscore/icon.cpp                  \
      libmscore/image.cpp                 \
      libmscore/imageStore.cpp            \
      libmscore/iname.cpp                 \
      libmscore/input.cpp                 \
      libmscore/instrchange.cpp           \
      libmscore/instrtemplate.cpp         \
      libmscore/instrument.cpp            \
      libmscore/interval.cpp              \
      libmscore/joinMeasure.cpp           \
      libmscore/key.cpp                   \
      libmscore/keyfinder.cpp             \
      libmscore/keysig.cpp                \
      libmscore/lasso.cpp                 \
      libmscore/layoutbreak.cpp           \
      libmscore/layout.cpp                \
      libmscore/line.cpp                  \
      libmscore/lyrics.cpp                \
      libmscore/measurebase.cpp           \
      libmscore/measure.cpp               \
      libmscore/midifile.cpp              \
      libmscore/mscore.cpp                \
      libmscore/navigate.cpp              \
      libmscore/note.cpp                  \
      libmscore/notedot.cpp               \
      libmscore/noteevent.cpp             \
      libmscore/ossia.cpp                 \
      libmscore/ottava.cpp                \
      libmscore/page.cpp                  \
      libmscore/part.cpp                  \
      libmscore/paste.cpp                 \
      libmscore/pedal.cpp                 \
      libmscore/pitch.cpp                 \
      libmscore/pitchspelling.cpp         \
      libmscore/pos.cpp                   \
      libmscore/property.cpp              \
      libmscore/qzip.cpp                  \
      libmscore/range.cpp                 \
      libmscore/read114.cpp               \
      libmscore/rehearsalmark.cpp         \
      libmscore/rendermidi.cpp            \
      libmscore/repeat.cpp                \
      libmscore/repeatlist.cpp            \
      libmscore/rest.cpp                  \
      libmscore/revisions.cpp             \
      libmscore/score.cpp                 \
      libmscore/scorefile.cpp             \
      libmscore/segment.cpp               \
      libmscore/segmentlist.cpp           \
      libmscore/select.cpp                \
      libmscore/shadownote.cpp            \
      libmscore/sig.cpp                   \
      libmscore/simpletext.cpp            \
      libmscore/slur.cpp                  \
      libmscore/spacer.cpp                \
      libmscore/spanner.cpp               \
      libmscore/sparm.cpp                 \
      libmscore/splitMeasure.cpp          \
      libmscore/staff.cpp                 \
      libmscore/staffstate.cpp            \
      libmscore/stafftext.cpp             \
      libmscore/stafftype.cpp             \
      libmscore/stem.cpp                  \
      libmscore/style.cpp                 \
      libmscore/symbol.cpp                \
      libmscore/sym.cpp                   \
      libmscore/system.cpp                \
      libmscore/tablature.cpp             \
      libmscore/tempo.cpp                 \
      libmscore/tempotext.cpp             \
      libmscore/text.cpp                  \
      libmscore/textframe.cpp             \
      libmscore/textline.cpp              \
      libmscore/timesig.cpp               \
      libmscore/transpose.cpp             \
      libmscore/tremolobar.cpp            \
      libmscore/tremolo.cpp               \
      libmscore/trill.cpp                 \
      libmscore/tuplet.cpp                \
      libmscore/undo.cpp                  \
      libmscore/utils.cpp                 \
      libmscore/velo.cpp                  \
      libmscore/volta.cpp                 \
      libmscore/xml.cpp                   \
      synti/chan.cpp                      \
      synti/chorus.cpp                    \
      synti/conv.cpp                      \
      synti/fluid.cpp                     \
      synti/gen.cpp                       \
      synti/mod.cpp                       \
      synti/rev.cpp                       \
      synti/sf1.cpp                       \
      synti/sf2.cpp                       \
      synti/sf3.cpp                       \
      synti/sf4.cpp                       \
      synti/sf5.cpp                       \
      synti/sf6.cpp                       \
      synti/sf7.cpp                       \
      synti/sf8.cpp                       \
      synti/sf.cpp                        \
      synti/sfont.cpp                     \
      synti/voice.cpp \
    localserver.cpp \
    android/jni/chmode.c \
    libmscore/bsymbol.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/origo/QtApplication.java \
    android/src/org/kde/necessitas/origo/QtActivity.java \
    android/src/org/kde/necessitas/origo/CopyResources.java \
    android/src/org/kde/necessitas/origo/QAudioManager.java \
    android/src/org/kde/necessitas/industrius/QtEditText.java \
    android/src/org/kde/necessitas/industrius/QtInputConnection.java \
    android/src/org/kde/necessitas/industrius/QtLayout.java \
    android/src/org/kde/necessitas/industrius/QtNative.java \
    android/src/org/kde/necessitas/industrius/QtSurface.java \
    android/src/org/kde/necessitas/industrius/QtNativeLibrariesDir.java \
    android/src/org/kde/necessitas/industrius/QtActivityDelegate.java \
    android/src/org/kde/necessitas/mobile/QtAndroidContacts.java \
    android/src/org/kde/necessitas/mobile/QtBroadcastReceiver.java \
    android/src/org/kde/necessitas/mobile/QtCamera.java \
    android/src/org/kde/necessitas/mobile/QtFeedback.java \
    android/src/org/kde/necessitas/mobile/QtLocation.java \
    android/src/org/kde/necessitas/mobile/QtMediaPlayer.java \
    android/src/org/kde/necessitas/mobile/QtSensors.java \
    android/src/org/kde/necessitas/mobile/QtSystemInfo.java \
    android/version.xml \
    android/res/layout/splash.xml \
    android/res/drawable/icon.png \
    android/res/drawable/logo.png \
    android/res/values-zh-rTW/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/values-id/strings.xml \
    android/res/values-es/strings.xml \
    android/res/values-ja/strings.xml \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/values-et/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values-el/strings.xml \
    android/res/drawable-ldpi/icon.png \
    android/res/values-ru/strings.xml \
    android/res/values-ro/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-it/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/drawable-hdpi/icon.png \
    android/res/values-rs/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/drawable-mdpi/icon.png \
    android/AndroidManifest.xml \
    buildCount.mk

HEADERS += seq.h scoreview.h downloadmanager.h customnetworkmanagerfactory.h androidaudio.h \
    libmscore/accidental.h              \
    libmscore/arpeggio.h                \
    libmscore/articulation.h            \
    libmscore/audio.h                   \
    libmscore/barline.h                 \
    libmscore/beam.h                    \
    libmscore/bend.h                    \
    libmscore/box.h                     \
    libmscore/bracket.h                 \
    libmscore/breath.h                  \
    libmscore/bsp.h                     \
    libmscore/bsymbol.h                 \
    libmscore/chord.h                   \
    libmscore/chordline.h               \
    libmscore/chordlist.h               \
    libmscore/chordrest.h               \
    libmscore/clef.h                    \
    libmscore/cleflist.h                \
    libmscore/cursor.h                  \
    libmscore/drumset.h                 \
    libmscore/dsp.h                     \
    libmscore/duration.h                \
    libmscore/durationtype.h            \
    libmscore/dynamic.h                 \
    libmscore/element.h                 \
    libmscore/elementlayout.h           \
    libmscore/elementmap.h              \
    libmscore/event.h                   \
    libmscore/event_p.h                 \
    libmscore/excerpt.h                 \
    libmscore/exportmidi.h              \
    libmscore/fifo.h                    \
    libmscore/figuredbass.h             \
    libmscore/fingering.h               \
    libmscore/fraction.h                \
    libmscore/fret.h                    \
    libmscore/glissando.h               \
    libmscore/hairpin.h                 \
    libmscore/harmony.h                 \
    libmscore/hook.h                    \
    libmscore/icon.h                    \
    libmscore/image.h                   \
    libmscore/imageStore.h              \
    libmscore/iname.h                   \
    libmscore/input.h                   \
    libmscore/instrchange.h             \
    libmscore/instrtemplate.h           \
    libmscore/instrument.h              \
    libmscore/instrument_p.h            \
    libmscore/interval.h                \
    libmscore/keyfinder.h               \
    libmscore/key.h                     \
    libmscore/keysig.h                  \
    libmscore/lasso.h                   \
    libmscore/layoutbreak.h             \
    libmscore/layout.h                  \
    libmscore/line.h                    \
    libmscore/lyrics.h                  \
    libmscore/measurebase.h             \
    libmscore/measure.h                 \
    libmscore/midifile.h                \
    libmscore/midipatch.h               \
    libmscore/mscore.h                  \
    libmscore/mscoreview.h              \
    libmscore/navigate.h                \
    libmscore/noscript.h                \
    libmscore/notedot.h                 \
    libmscore/noteevent.h               \
    libmscore/note.h                    \
    libmscore/ossia.h                   \
    libmscore/ottava.h                  \
    libmscore/page.h                    \
    libmscore/part.h                    \
    libmscore/pedal.h                   \
    libmscore/pitch.h                   \
    libmscore/pitchspelling.h           \
    libmscore/pitchvalue.h              \
    libmscore/pos.h                     \
    libmscore/property.h                \
    libmscore/qzipreader_p.h            \
    libmscore/qzipwriter_p.h            \
    libmscore/range.h                   \
    libmscore/rehearsalmark.h           \
    libmscore/repeat.h                  \
    libmscore/repeatlist.h              \
    libmscore/rest.h                    \
    libmscore/revisions.h               \
    libmscore/score.h                   \
    libmscore/segment.h                 \
    libmscore/segmentlist.h             \
    libmscore/select.h                  \
    libmscore/sequencer.h               \
    libmscore/shadownote.h              \
    libmscore/sig.h                     \
    libmscore/simpletext.h              \
    libmscore/slur.h                    \
    libmscore/slurmap.h                 \
    libmscore/spacer.h                  \
    libmscore/spanner.h                 \
    libmscore/spannermap.h              \
    libmscore/sparm.h                   \
    libmscore/sparm_p.h                 \
    libmscore/spatium.h                 \
    libmscore/staff.h                   \
    libmscore/staffstate.h              \
    libmscore/stafftext.h               \
    libmscore/stafftype.h               \
    libmscore/stem.h                    \
    libmscore/style.h                   \
    libmscore/style_p.h                 \
    libmscore/symbol.h                  \
    libmscore/sym.h                     \
    libmscore/system.h                  \
    libmscore/tablature.h               \
    libmscore/tempo.h                   \
    libmscore/tempotext.h               \
    libmscore/textframe.h               \
    libmscore/text.h                    \
    libmscore/textline.h                \
    libmscore/tiemap.h                  \
    libmscore/timesig.h                 \
    libmscore/tremolobar.h              \
    libmscore/tremolo.h                 \
    libmscore/trill.h                   \
    libmscore/tuplet.h                  \
    libmscore/tupletmap.h               \
    libmscore/undo.h                    \
    libmscore/utils.h                   \
    libmscore/velo.h                    \
    libmscore/volta.h                   \
    libmscore/xml.h \
    buildNumber.h \
    droptarget.h \
    localserver.h

