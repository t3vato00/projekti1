#ifndef KAYTTAJA_H
#define KAYTTAJA_H

#include <QDialog>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <functional>
#include <QMessageBox>

#include <QTimer>
#include "ui/login/loginpage.h"
#include "rfid/rfid_reader.h"

namespace Ui {
class user;
}

class user : public QDialog
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = 0);
    ~user();

private slots:
    void on_add_user_clicked();

    void on_clear_clicked();

    void closeMessage()
    {
        msgr.close();
    }

private:
    Ui::user *ui;
    QString nimi;
    QString kortti_id;
    QSqlQuery add_user;
    QCryptographicHash * hash;
    rfid_reader * riider;
    loginpage login;
    int row_amount;
    void load_users();
    void add_row_to_list(QString, QString, QString);
    QString hash_pass(QString);
    bool stop_timer;
    QTimer * Timer;
    QMessageBox msgr;
};

#endif // KAYTTAJA_H
