#include "ui/login/loginpage.h"
#include "ui_loginpage.h"

loginpage::loginpage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginpage)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton, SIGNAL(clicked()),this, SLOT(sendLogin()));
    rfReader = new rfid_reader("COM11");//jep
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
    emit loginClicked(0);
}
void loginpage::rfid_ok(QString )
{
    emit loginClicked(1);
}
