#-------------------------------------------------
#
# Project created by QtCreator 2014-04-15T10:13:55
#
#-------------------------------------------------

QT       += core gui sql
 QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = inventaari
TEMPLATE = app

QMAKE_CXXFLAGS += --std=c++11

SOURCES += main.cpp \
    ui/mainwindow.cpp \
    ui/mainmenu/mainmenu.cpp \
    ui/login/loginpage.cpp \
    ui/products/product_management.cpp \
    db/products/product_model.cpp \
    ui/sales/sale.cpp \
    ui/users/user_management.cpp \
    db/products/product.cpp \
    db/utilities.cpp \
	 db/users/login.cpp \
    db/sales/sales_row.cpp \
    db/sales/sales_event.cpp \
    ui/sales/sales_tracking.cpp \
    ui/users/read_card_dialog.cpp \
    ui/sales/selling.cpp

HEADERS  += \
    ui/mainwindow.h \
    ui/mainmenu/mainmenu.h \
    ui/login/loginpage.h \
    ui/products/product_management.h \
    db/products/product_model.h \
    ui/sales/sale.h \
    ui/users/user_management.h \
    db/products/product.h \
    db/utilities.h \
	 db/users/user.h \
	 db/users/login.h \
    db/sales/sales_row.h \
    db/sales/sales_event.h \
    ui/sales/sales_tracking.h \
    ui/users/read_card_dialog.h \
    ui/sales/selling.h

RESOURCES += \
    resource.qrc

FORMS += \
    ui/products/product_management.ui \
    ui/mainmenu/mainmenu.ui \
    ui/login/loginpage.ui \
    ui/sales/sale.ui \
    ui/users/user_management.ui \
    ui/sales/sales_tracking.ui \
    ui/users/read_card_dialog.ui \
    ui/sales/selling.ui

INCLUDEPATH += $$PWD/qextserial
DEPENDPATH += $$PWD/qextserial

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-inventaari-Desktop_Qt_5_2_1_MinGW_32bit-Debug/release -lQt5ExtSerialPort1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-qextserialport-Desktop_Qt_5_2_1_MinGW_32bit-Release/debug/ -lQt5ExtSerialPort1
else:unix: LIBS += -L$$PWD/../build-qextserialport -lQt5ExtSerialPort -L$$PWD/../build-rfid -lrfid_reader_dll
