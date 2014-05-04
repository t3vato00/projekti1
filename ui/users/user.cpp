#include <QTableWidget>
#include <QTableView>
#include <QString>
#include <QCompleter>
#include <QVector>
#include <QDateTime>
#include <QMessageBox>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QSqlError>

#include "ui/users/user.h"
#include "ui_user.h"
#include "rfid/rfid_reader.h"

#include <qnetwork.h>
#include <QtNetwork/QNetworkAccessManager>
#include <QByteArray>

user::user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user),
       add_user()
{

    hash = new QCryptographicHash(QCryptographicHash::Sha1);
    row_amount = 0;
    ui->setupUi(this);
    add_user.prepare("INSERT INTO users(name, card_id, user_password) VALUES(?,?,?);");
    ui->userView->setRowHeight(row_amount,100);
    QStringList aheaders;
    aheaders << "Nimi" << "Kortti ID" << "Salasana";

    for(int j=0;j<3;j++)
    {
        ui->userView->insertColumn(j);
        ui->userView->setHorizontalHeaderLabels(aheaders);
        ui->userView->setColumnWidth(j,443);
    }
    load_users();

}

void user::load_users()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM users;");
    query.exec();
    while(query.next()){
        qDebug() << query.value(0).toString();
        qDebug() << query.value(1).toString();
        qDebug() << query.value(2).toString();
        add_row_to_list(query.value(0).toString(),query.value(1).toString(),query.value(2).toString());
    }
    query.finish();

}

void user::add_row_to_list(QString name, QString card_id, QString password)
{

    ui->userView->insertRow(row_amount);
    QTableWidgetItem* userName = new QTableWidgetItem;
    QTableWidgetItem* userCodeID = new QTableWidgetItem;
    QTableWidgetItem* userPassword = new QTableWidgetItem;

    userName->setText(name);
    userCodeID->setText(card_id);
    userPassword->setText(/*hash_pass(*/password);
    userName->setTextAlignment(Qt::AlignCenter);
    userCodeID->setTextAlignment(Qt::AlignCenter);
    userPassword->setTextAlignment(Qt::AlignCenter);
    ui->userView->setItem(row_amount,0,userName);
    ui->userView->setItem(row_amount,1,userCodeID);
    ui->userView->setItem(row_amount,2,userPassword);

}

user::~user()
{
    delete ui;
}


inline QString normalize_string_input( QString const & q )
{
    return q.normalized(QString::NormalizationForm_C).trimmed();
}

void database_Error( QString const msg )
{
    QMessageBox msgb;

    msgb.setText(msg);
    msgb.setIcon(QMessageBox::Critical);
    msgb.exec();
}

void invalid_Value( QString const msg )
{
    QMessageBox msgb;

    msgb.setText(msg);
    msgb.setIcon(QMessageBox::Critical);
    msgb.exec();
}

void user::on_add_user_clicked()
{
    QString name = normalize_string_input(ui->lineName->text());
    QString card_id = normalize_string_input(ui->lineID->text());
    QString password = normalize_string_input(ui->linePass->text());
    password = hash_pass(password);



    if(card_id.length() != 10)
    {
        invalid_Value( "Invalid card id '" + card_id + "'." );
        return;
    }
    add_user.bindValue(0,name);
    add_user.bindValue(1,card_id);
    add_user.bindValue(2,password);
    bool ok = add_user.exec();
    if(!ok)
        database_Error ("Database Error: " + add_user.lastError().text() );
    add_user.finish();
    add_row_to_list(name,card_id,password);
    on_clear_clicked();

}

void user::on_clear_clicked()
{
    ui->lineName->setText("");
    ui->lineID->setText("");
    ui->linePass->setText("");
}

QString user::hash_pass(QString pass)
{
    QByteArray hashed_pass = hash->hash(pass.toUtf8(),QCryptographicHash::Sha1);
    return hashed_pass.toHex();
}

void user::on_pushButton_clicked()
{
    bool b;
    //int count_down = 5;
    //Timer = new QTimer(this);
    login->read_rfid([b,this](QString rfid2){
    QSqlQuery dumb;
    dumb.prepare("INSERT INTO users (id_dumb) VALUES (?);");
    dumb.bindValue(3,rfid2);
    dumb.exec();
    dumb.finish();
    this->login;
    });

    //msgr.setText("Testi");
    //msgr.show();
}
