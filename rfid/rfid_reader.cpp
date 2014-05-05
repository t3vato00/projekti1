#include <stdio.h>
#include "rfid/rfid_reader.h"
#include <QDebug>

rfid_reader::rfid_reader(QString pPort)
{
    portName = pPort;
    connect(&timer, SIGNAL(timeout()),this,SLOT(tick()));
}

bool rfid_reader::openCOMPort()
{
    serialPort.setPortName(portName);
    serialPort.setQueryMode(QextSerialPort::EventDriven);
    serialPort.setBaudRate(BAUD9600);
    serialPort.setFlowControl(FLOW_HARDWARE);
    serialPort.setParity(PAR_NONE);
    serialPort.setDataBits(DATA_8);
    serialPort.setStopBits(STOP_1);
    bool returnValue = serialPort.open(QIODevice::ReadWrite);
    return returnValue;
}

void rfid_reader::closeCOMPort()
{
    serialPort.close();
}

void rfid_reader::tick()
{
    if(ending)
    {
        serialPort.read(10);
        timer.stop();
        closeCOMPort();
    }
    if(!first)
    {
        QString hexNum, cardSerialNumber;
        char data[11], temp[11];
        int bytesRead;

        bytesRead = serialPort.read(data,10);
        data[bytesRead] = '\0';
        if (bytesRead > 0)
        {
            for(int i=0;i<5;i++)
            {
                sprintf(temp,"%08X", data[i]);
                hexNum = temp;
                cardSerialNumber = cardSerialNumber + hexNum.right(2);
            }
           if(cardSerialNumber.at(0)==QChar('8'))
           {
               cardSerialNumber = "";
           }

        }else
        {
         cardSerialNumber = "";
        }
        if(cardSerialNumber=="")
        {
            if(missess>=3)
            {
                if(prevRFID!="")
                    emit norfid();
                prevRFID = "";
            }else
            {
                missess++;
            }
        }else
        {
            missess = 0;
            if(cardSerialNumber==prevRFID)
            {

            }else
            {
                prevRFID = cardSerialNumber;
                emit rfid(prevRFID);
            }
        }
    }
    serialPort.write("U",1);
}
bool rfid_reader::start()
{
    if(openCOMPort())
    {
        timer.setInterval(1000);
        timer.start(1000);
        first = false;
        missess = 0;
        ending = false;
        return true;
    }
    return false;
}
void rfid_reader::stop()
{
   ending = true;

}

rfid_reader *
rfid_reader::
create(QString pPort)
{
	return new rfid_reader(pPort);
}

void
rfid_reader::
destroy(rfid_reader * t)
{
	delete t;
}

