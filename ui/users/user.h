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
    inline QString kortti_id() const {return _kortti_id;}

private:
    Ui::user *ui;
    QString _nimi;
    QString _kortti_id = "kortinnumero";

};

#endif // KAYTTAJA_H
