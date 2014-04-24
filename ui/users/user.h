#ifndef KAYTTAJA_H
#define KAYTTAJA_H

#include <QDialog>
#include <QNetworkReply>

namespace Ui {
class user;
}

class user : public QDialog
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = 0);
    ~user();

private:
    Ui::user *ui;

public slots:

};

#endif // KAYTTAJA_H
