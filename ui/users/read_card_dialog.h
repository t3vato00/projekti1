#ifndef READ_CARD_DIALOG_H
#define READ_CARD_DIALOG_H

#include <QWidget>
#include <db/users/login.h>

namespace Ui {
class read_card_dialog;
}

class read_card_dialog : public QWidget
{
    Q_OBJECT

public:
    explicit read_card_dialog(QWidget *parent = 0);
    ~read_card_dialog();

private slots:
	void show_card_dialog( login::read_rfid_status stat );

private:
    Ui::read_card_dialog *ui;
};

#endif // READ_CARD_DIALOG_H
