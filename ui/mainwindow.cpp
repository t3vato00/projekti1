#include "ui/mainwindow.h"
#include <QStackedWidget>
#include <QtGui>
#include <qtoolbar.h>
#include <qaction.h>

#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent)
{
   createConnection();

   login_page = new loginpage();
   mainpage = new mainmenu();
   tuote = new product_management();
   myynti = new sale();
   kayttajat = new user();
   salestrack = new sales_tracking();
   sell = new Selling();

   stackedWidget = new QStackedWidget;
   stackedWidget->insertWidget(0,login_page);
   stackedWidget->insertWidget(1,mainpage);
   stackedWidget->insertWidget(2,tuote);
   stackedWidget->insertWidget(3,myynti);
   stackedWidget->insertWidget(4,kayttajat);
   stackedWidget->insertWidget(5,salestrack);
   stackedWidget->insertWidget(6,sell);

   QObject::connect(login_page, SIGNAL(loginClicked(int)),stackedWidget, SLOT(setCurrentIndex(int)));
   QObject::connect(login_page, SIGNAL(loginClicked(int)),this, SLOT(show_toolbar()));
   QObject::connect(mainpage, SIGNAL(send_page_index(int)),stackedWidget, SLOT(setCurrentIndex(int)));
   QObject::connect(this, SIGNAL(to_main_signal(int)),stackedWidget, SLOT(setCurrentIndex(int)));

   setFixedHeight(768);
   setFixedWidth(1366);
   this->showFullScreen();
   setCentralWidget(stackedWidget);
}

MainWindow::~MainWindow()
{
    delete login_page;
    delete tuote;
    delete myynti;
    delete kayttajat;
}

void MainWindow::show_toolbar()
{
    create_actions();
    create_toolbars();
    QObject::disconnect(login_page, SIGNAL(loginClicked(int)),this, SLOT(show_toolbar()));
}

void MainWindow::create_toolbars()
 {
     editToolBar = addToolBar(tr(""));
     editToolBar->addAction(ToMainmenuAct);
     editToolBar->setOrientation(Qt::Vertical);
     editToolBar->setFloatable(false);

}

void MainWindow::to_mainmenu()
 {
    emit to_main_signal(1);
 }

void MainWindow::create_actions()
{
    ToMainmenuAct = new QAction(QIcon(":images/undo.png"), tr("&Päävalikkoon"), this);
    ToMainmenuAct->setStatusTip(tr("Päävalikkoon"));
    QObject::connect(ToMainmenuAct, SIGNAL(triggered()), this, SLOT(to_mainmenu()));
}
bool MainWindow::createConnection(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("inventaari");
    db.setUserName("root");
    db.setPassword("");//asdklielxkjoijdneidkod
    if (!db.open()) {
        qDebug() << "Database error occurred";
        return false;
    }
    return true;
}

