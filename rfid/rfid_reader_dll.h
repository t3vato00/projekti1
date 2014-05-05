#ifndef RFID_READER_DLL_H
#define RFID_READER_DLL_H
#include <rfid/rfid_reader_global.h>
#include <rfid/rfid_reader.h>

class rfid_reader_dll 
{
public:
	static rfid_reader * RFID_READER_DLLSHARED_EXPORT create(QString pPort);
	static void RFID_READER_DLLSHARED_EXPORT destroy(rfid_reader * t);
};

#endif // RFID_READER_DLL_H
