#-------------------------------------------------
#
# Project created by QtCreator 2018-12-03T14:21:01
#
#-------------------------------------------------

QT += core gui
QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Battleship
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    cell.cpp \
    cellboard.cpp \
    battleshipgame.cpp \
    player.cpp \
    ServerCommunicator.cpp \
    button.cpp

HEADERS += \
    cell.h \
    cellboard.h \
    battleshipgame.h \
    player.h \
    ServerCommunicator.h \
    config.h \
    button.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += /usr/local/opt/openssl/include
INCLUDEPATH += /usr/local/opt/cpprestsdk/include
INCLUDEPATH += /usr/local/opt/boost/include

macx: LIBS += -L/usr/local/opt/openssl/lib/ -lcrypto
LIBS += -lcpprest -lcrypto -lssl -lboost_system -lboost_chrono
LIBS += -L/usr/local/opt/cpprestsdk/lib/
LIBS += -L/usr/local/opt/boost/lib/
macx: LIBS += -lboost_thread-mt
unix:!macx|win: LIBS += -lboost_thread

RESOURCES += \
    images.qrc
