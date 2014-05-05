#ifndef RFID_READER_H
#define RFID_READER_H
#include <QThread>
#include <QTimer>
#include <qextserial/qextserialport.h>
#include <rfid/rfid_reader_global.h>

class rfid_reader : public QObject
{
    Q_OBJECT

private:
    rfid_reader(QString pPort);
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
    bool RFID_READER_DLLSHARED_EXPORT start();
    void RFID_READER_DLLSHARED_EXPORT stop();

	 static rfid_reader * RFID_READER_DLLSHARED_EXPORT create(QString pPort);
	 static void RFID_READER_DLLSHARED_EXPORT destroy(rfid_reader * t);
};

#endif // RFID_READER_H
