
#include <rfid/rfid_reader_dll.h>

rfid_reader *
rfid_reader_dll::
create(QString pPort)
{
	return new rfid_reader(pPort);
}

void
rfid_reader_dll::
destroy(rfid_reader * t)
{
	delete t;
}

