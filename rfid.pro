#-------------------------------------------------
#
# Project created by QtCreator 2014-04-28T17:06:12
#
#-------------------------------------------------

QT -= gui

TARGET = rfid_reader_dll
TEMPLATE = lib

DEFINES += RFID_READER_DLL_LIBRARY

SOURCES += rfid/rfid_reader.cpp

HEADERS += rfid/rfid_reader.h
HEADERS += rfid/rfid_reader_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += $$PWD/qextserial
DEPENDPATH += $$PWD/qextserial

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../build-qextserialport-Desktop_Qt_5_2_1_MinGW_32bit-Release/release/ -lQt5ExtSerialPortd1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../build-qextserialport-Desktop_Qt_5_2_1_MinGW_32bit-Release/debug/ -lQt5ExtSerialPortd1
else:unix: LIBS += -L$$PWD/../build-qextserialport -lQt5ExtSerialPort

