#ifndef RFID_READER_DLL_H
#define RFID_READER_DLL_H

#include <QtCore>
#include <QThread>
#include <QTimer>
#include "C:/Users/Tommi/Desktop/Koulu/Projekti/git/inventaari/qextserial/qextserialport.h"
#include "../../ui/login/loginpage.h"

#include "rfid_reader_dll_global.h"

class Rfid_reader_dll : public QObject
{
    Q_OBJECT
private:
    QTimer timer;
    QextSerialPort serialPort;
    QString portName;
    bool openCOMPort();
    void closeCOMPort();
    bool first;
    unsigned missess;
    bool ending;

private slots:
    void tick();
signals:
    void rfid(QString);
    void norfid();
public:
    bool start();
    void stop();
    QString prevRFID;
    //Rfid_reader_dll(QString pPort);
    Rfid_reader_dll(QString pPort);

};

#endif // RFID_READER_DLL_H
