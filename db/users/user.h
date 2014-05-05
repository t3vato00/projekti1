#ifndef HEADER__DB_USERS_USER
#define HEADER__DB_USERS_USER

#include <QString>

class user
{
	QString _name;
	QString _card_id;

public:
	inline user() : _name(QStringLiteral("")), _card_id(QStringLiteral("")) { }
	inline user( QString name, QString card_id ) : _name(name), _card_id(card_id) { }
	inline QString name() const { return _name; }
	inline QString card_id() const { return _card_id; }
};

#endif // HEADER__DB_USERS_USER
