#ifndef KAYTTAJA_H
#define KAYTTAJA_H

#include <QDialog>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <functional>
#include <QMessageBox>

#include <QTimer>
#include <db/users/login.h>

namespace Ui {
class user_management;
}

class user_management : public QDialog
{
    Q_OBJECT

public:
    explicit user_management(QWidget *parent = 0);
    ~user_management();

private slots:
    void on_add_user_clicked();

    void on_clear_clicked();

    void on_read_card();

    void closeMessage()
    {
        msgr.close();
    }

private:
    Ui::user_management *ui;
    QString nimi;
    QString kortti_id;
    QSqlQuery add_user;
    QCryptographicHash * hash;
    int row_amount;
    void load_users();
    void add_row_to_list(QString, QString, QString);
    QString hash_pass(QString);
    bool stop_timer;
    QTimer * Timer;
    QMessageBox msgr;

};

#endif // KAYTTAJA_H
