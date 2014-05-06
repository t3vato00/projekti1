#ifndef HEADER__DB_USERS_USER
#define HEADER__DB_USERS_USER

#include <QString>

class user
{
	QString _name;
	QString _card_id;
	bool _super;

public:
	inline user() : _name(QStringLiteral("")), _card_id(QStringLiteral("")), _super(false) { }
	inline user( QString name, QString card_id, bool super = false ) : _name(name), _card_id(card_id), _super(super) { }
	inline QString name() const { return _name; }
	inline QString card_id() const { return _card_id; }
	inline bool super() const { return _super; }
};

#endif // HEADER__DB_USERS_USER
