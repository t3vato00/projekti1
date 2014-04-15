#ifndef KAYTTAJA_H
#define KAYTTAJA_H

#include <QDialog>

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
    QString nimi;
    QString kortti_id;

};

#endif // KAYTTAJA_H
