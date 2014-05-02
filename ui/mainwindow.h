#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qstackedwidget.h>
#include "ui/login/loginpage.h"
#include "ui/products/product_management.h"
#include "ui/sales/sale.h"
#include "ui/sales/sales_tracking.h"
#include "ui/users/user.h"
#include "ui/mainmenu/mainmenu.h"
#include "ui/sales/selling.h"

class MainWindow : public QMainWindow
{    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool createConnection();


private slots:
    void to_mainmenu();
    void show_toolbar();

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
    user * kayttajat;
    sales_tracking *salestrack;
    product_management *tuote;
    sale* myynti;
    QStackedWidget *stackedWidget;
    Selling *sell;
};

#endif // MAINWINDOW_H
