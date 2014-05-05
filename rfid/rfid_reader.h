#ifndef RFID_READER_H
#define RFID_READER_H
#include <QThread>
#include <QTimer>
#include <qextserial/qextserialport.h>
#include <rfid/rfid_reader_global.h>

class RFID_READER_DLLSHARED_EXPORT rfid_reader : public QObject
{
    Q_OBJECT

    QTimer timer;
    QextSerialPort serialPort;
    QString portName;
    bool openCOMPort();
    void closeCOMPort();
    bool first;
    unsigned missess;
    bool ending;
    QString prevRFID;

private slots:
    void tick();

signals:
    void RFID_READER_DLLSHARED_EXPORT norfid();
    void RFID_READER_DLLSHARED_EXPORT rfid(QString);

public:
    rfid_reader(QString pPort);

    bool RFID_READER_DLLSHARED_EXPORT start();
    void RFID_READER_DLLSHARED_EXPORT stop();

};

#endif // RFID_READER_H
