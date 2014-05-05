
#include <db/users/login.h>
#include <db/utilities.h>
#include <QDebug>

login * login::inst = nullptr;

login::
login()
: qcard( "SELECT name FROM users WHERE card_id = ?;" )
{
	qDebug() << "login init";
	reader = rfid_reader::create("/dev/ttyUSB0");
	QObject::connect(reader,&rfid_reader::rfid,this,&login::rfid);
	QObject::connect(reader,&rfid_reader::norfid,this,&login::norfid);
	QObject::connect(this,&login::show_card_dialog,[]( read_rfid_status st ) { qDebug() << "card dialog:" << st ; });
	if( !reader->start() )
		qCritical( "unable to start rfid reader!" );
}

login::
~login()
{
	reader->stop();
	rfid_reader::destroy(reader);
}

void
login::
rfid( QString id )
{
	if( read_stat == not_reading )
	{
		if(!logged)
		{
			qDebug() << "login: begin!";
			qcard.bindValue( 0, id );
			if( !qcard.exec() )
			{
				qDebug() << "login: database error!";
				database_error( qcard.lastError() );
			}
			if( !qcard.next() )
			{
				qDebug() << "login: card not found!";
				return;
			}

			QString name = qcard.value(0).toString();
			logged_user = user( name, id );
			emit logged_in( logged_user );
			logged = true;
		}
	}
	else if( read_stat == new_card )
	{
		if( id != logged_user.card_id() )
		{
			read_id = id;
			read_stat = old_card;
			emit show_card_dialog(read_stat);
		}
	}
	else if( read_stat == old_card )
	{
		if( id == logged_user.card_id() )
		{
			read_rfid_handler( id );
			read_stat = not_reading;
			emit show_card_dialog(read_stat);
		}
	}
}

void
login::
norfid()
{
	if( read_stat == not_reading )
	{
		if( logged )
		{
			logged = false;
			emit logged_out( logged_user );
		}
	}
}

login &
login::
singleton()
{
	if( inst == nullptr )
		inst = new login();

	return * inst;
}

void
login::
read_rfid( std::function<void(QString)> h )
{
	if( read_stat != not_reading )
		qFatal( "called read_rfid while already reading!" );
	if( !logged )
		qFatal( "called read_rfid while not logged in!" );

	read_stat = new_card;
	emit show_card_dialog(read_stat);
}

bool
login::
interrupt_read_rfid()
{
	if( !logged )
		return false;
	if( read_stat == not_reading )
		return false;
	
	read_stat = not_reading;
	emit show_card_dialog(read_stat);

	logged = false;
	emit logged_out( logged_user );

	return true;
}

