#include "ui/login/loginpage.h"
#include "ui_loginpage.h"
#include "db/users/user.h"
#include "db/users/login.h"
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>

loginpage::loginpage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginpage)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &loginpage::fake_login);
}

loginpage::~loginpage()
{
    delete ui;
}

void
loginpage::
fake_login()
{
	emit login::singleton().logged_in( user( "test_user", "0123456789" ) );
}

