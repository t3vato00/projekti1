#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>

namespace Ui {
class mainmenu;
}

class mainmenu : public QDialog
{
    Q_OBJECT

public:
    explicit mainmenu(QWidget *parent = 0);
    ~mainmenu();

public slots:
    void send_page(int);//int

signals:
    void send_page_index(int page_index);


private:
    Ui::mainmenu *ui;
};

#endif // MAINMENU_H
