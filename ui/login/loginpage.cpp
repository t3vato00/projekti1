#include "ui/login/loginpage.h"
#include "ui_loginpage.h"
#include "ui/users/user.h"
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>

loginpage::loginpage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginpage)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton, SIGNAL(clicked()),this, SLOT(sendLogin()));
    rfReader = new Rfid_reader_dll("COM11");
    rfReader->start();
    QObject::connect(rfReader, SIGNAL(norfid()),this, SLOT(rfid_noup()));
    QObject::connect(rfReader, SIGNAL(rfid(QString)),this, SLOT(rfid_ok(QString)));

}

loginpage::~loginpage()
{
    delete ui;
}

void loginpage::sendLogin()
{
    emit loginClicked(1);
}

void loginpage::rfid_noup()
{
    if(reading_rfid)
    {
    }else
    emit loginClicked(0);
}
void loginpage::rfid_ok(QString )
{
    if(reading_rfid)
    {
    }else
    emit loginClicked(1);
}

void loginpage::read_rfid(std::function<void(QString)>h)
{

    if(reading_rfid)
    {
        qFatal("read_rfid while read already active");
        exit(1);
    }
    read_rfid_handler = h;
    reading_rfid = true;
    QSqlQuery dumb;
    QString rfid2 = "Hello";
    QString name2 = "hello";
    QString id = "123982";
    QString user_pass = "asd";
    dumb.prepare("INSERT INTO users (name, card_id, user_password, id_dumb) VALUES (?,?,?,?);");
    dumb.bindValue(0,name2);
    dumb.bindValue(1,id);
    dumb.bindValue(2,user_pass);
    dumb.bindValue(3,rfid2);
    dumb.exec();
    dumb.finish();
    reading_rfid = false;
}


