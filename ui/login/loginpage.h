#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QDialog>
#include <functional>
#include <rfid/rfid_reader.h>
#include <db/users/user.h>

class Rfid_reader_dll;
namespace Ui {
class loginpage;
}

class loginpage : public QDialog
{
    Q_OBJECT

public:
    explicit loginpage(QWidget *parent = 0);
    ~loginpage();

private:
    Ui::loginpage *ui;

public:
    void fake_login();
};

#endif // LOGINPAGE_H
