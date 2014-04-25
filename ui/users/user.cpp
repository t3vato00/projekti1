#include "ui/users/user.h"
#include "ui_user.h"

#include <QByteArray>

user::user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);
}
user::~user()
{
    delete ui;
}
