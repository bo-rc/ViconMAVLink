#-------------------------------------------------
#
# Project created by QtCreator 2017-11-27T15:28:14
#
#-------------------------------------------------

QT       += core gui widgets network concurrent

TARGET = ViconMAVLink
TEMPLATE = app

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    Drone.cpp \
    KalmanFilter.cpp \
    Sender.cpp \
    SenderWindow.cpp \
    Station.cpp \
    StationController.cpp \
    StationWindow.cpp \
    SenderController.cpp

HEADERS  += \
    lib/MAVLink2/common/common.h \
    lib/MAVLink2/common/mavlink.h \
    Drone.h \
    KalmanFilter.h \
    Sender.h \
    SenderWindow.h \
    Station.h \
    StationController.h \
    StationWindow.h \
    SenderController.h

FORMS    += \
    StationWindow.ui \
    SenderWindow.ui

unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/Vicon/ -lViconDataStreamSDK_CPP
unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/Vicon/ -lboost_system
unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/Vicon/ -lboost_thread

INCLUDEPATH += $$PWD/../../../../usr/local/include/Vicon
DEPENDPATH += $$PWD/../../../../usr/local/include/Vicon

unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/GeographicLib/ -lGeographic

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include

INCLUDEPATH += $$PWD/../../../../../include/
DEPENDPATH += $$PWD/../../../../../include/

DEFINES += GEOGRAPHICLIB_SHARED_LIB=0

win32: LIBS += -L$$PWD/../../../../../pkg-vc12-x64/GeographicLib-1.49/lib/ -lGeographic

INCLUDEPATH += $$PWD/../../../../../pkg-vc12-x64/GeographicLib-1.49/include
DEPENDPATH += $$PWD/../../../../../pkg-vc12-x64/GeographicLib-1.49/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../../../pkg-vc12-x64/GeographicLib-1.49/lib/Geographic.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../../../../pkg-vc12-x64/GeographicLib-1.49/lib/libGeographic.a

win32: LIBS += -L$$PWD/'../../../../../Program Files/Vicon/DataStream SDK/Win64/CPP/' -lViconDataStreamSDK_CPP

INCLUDEPATH += $$PWD/'../../../../../Program Files/Vicon/DataStream SDK/Win64/CPP'
DEPENDPATH += $$PWD/'../../../../../Program Files/Vicon/DataStream SDK/Win64/CPP'

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/'../../../../../Program Files/Vicon/DataStream SDK/Win64/CPP/ViconDataStreamSDK_CPP.lib'
else:win32-g++: PRE_TARGETDEPS += $$PWD/'../../../../../Program Files/Vicon/DataStream SDK/Win64/CPP/libViconDataStreamSDK_CPP.a'
