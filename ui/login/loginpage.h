#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QDialog>
#include <functional>
#include "rfid/rfid_reader_dll/rfid_reader_dll.h"
#include "rfid/rfid_reader_dll/rfid_reader_dll_global.h"
class Rfid_reader_dll;
namespace Ui {
class loginpage;
}

class loginpage : public QDialog
{
    Q_OBJECT

public:
    Rfid_reader_dll * rfReader;
    explicit loginpage(QWidget *parent = 0);
    ~loginpage();
    bool reading_rfid;
    std::function<void(QString)>read_rfid_handler;
    void read_rfid( std::function<void(QString)> h );

private:
    Ui::loginpage *ui;
public slots:
    void sendLogin();
    void rfid_noup();
    void rfid_ok(QString);

signals:
    void loginClicked(int);
};

#endif // LOGINPAGE_H
