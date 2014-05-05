#ifndef HEADER__DB_USERS_LOGIN
#define HEADER__DB_USERS_LOGIN

#include <QObject>
#include <QSqlQuery>
#include <db/users/user.h>
#include <rfid/rfid_reader.h>

class login : public QObject
{
	Q_OBJECT

public:
	enum read_rfid_status
	{
		not_reading,
		new_card,
		old_card
	};

	~login();
private:

	login();

	QSqlQuery qcard;

	read_rfid_status read_stat = not_reading;
	QString read_id;
	std::function<void(QString)> read_rfid_handler;

	rfid_reader * reader;

	static login * inst;

	bool logged = false;
	user logged_user;

private slots:
	void rfid( QString id );
	void norfid();

public:
	static login & singleton();

	void read_rfid( std::function<void(QString)> h );

signals:
	void show_card_dialog( read_rfid_status );
	void logged_in( user );
	void logged_out( user );

public slots:
	bool interrupt_read_rfid();
};

#endif // HEADER__DB_USERS_LOGIN
