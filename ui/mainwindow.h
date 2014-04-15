#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qstackedwidget.h>
#include "ui/login/loginpage.h"
#include "ui/products/product_management.h"
#include "ui/sales/sale.h"
#include "ui/users/user.h"
#include "ui/mainmenu/mainmenu.h"

class MainWindow : public QMainWindow
{    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool createConnection();

private slots:
    void ToMainmenu();
    void showToolBar();

signals:
     void ToMain_signal(int);

private:
    QAction *ToMainmenuAct;
    QToolBar *editToolBar;
    QMenu *editMenu;
    void create_toolbars();
    void create_actions();
    loginpage *login_page;
    mainmenu * mainpage;
    product_management *tuote;
    sale* myynti;
    user*  kayttajat;
    QStackedWidget *stackedWidget;
};

#endif // MAINWINDOW_H
