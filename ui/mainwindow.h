#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qstackedwidget.h>
#include "ui/login/loginpage.h"
#include "ui/products/product_management.h"
#include "ui/sales/sale.h"
#include "ui/sales/sales_tracking.h"
#include "db/users/login.h"
#include "ui/users/read_card_dialog.h"
#include "ui/users/user_management.h"
#include "ui/mainmenu/mainmenu.h"
#include "ui/sales/selling.h"

class MainWindow : public QMainWindow
{    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool createConnection();

private slots:
    void login();
    void logout();
	 void show_card_dialog( login::read_rfid_status stat );
    void to_mainmenu();

signals:
     void to_main_signal(int);

private:
    QAction *ToMainmenuAct;
    QToolBar *editToolBar;
    QMenu *editMenu;
    void create_toolbars();
    void create_actions();
    loginpage *login_page;
    mainmenu * mainpage;
    sales_tracking *salestrack;
    product_management *tuote;
	 user_management*  kayttajat;
	 read_card_dialog*  card_dialog;
    sale* myynti;
    QStackedWidget *stackedWidget;
	 int saved_view;
    Selling *sell;
};

#endif // MAINWINDOW_H
