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

#include <db/users/login.h>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent)
{
	createConnection();
	login_page = new loginpage();
	mainpage = new mainmenu();
	tuote = new product_management();
	myynti = new sale();
	card_dialog = new read_card_dialog();
	kayttajat = new user_management();
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
	stackedWidget->insertWidget(7,card_dialog);

	auto l = &login::singleton();
	QObject::connect(l, &login::logged_in, this, &MainWindow::login);
	QObject::connect(l, &login::logged_out, this, &MainWindow::logout);
	QObject::connect(l, &login::show_card_dialog, this, &MainWindow::show_card_dialog);
	QObject::connect(mainpage, SIGNAL(send_page_index(int)),stackedWidget, SLOT(setCurrentIndex(int)));
	QObject::connect(this, SIGNAL(to_main_signal(int)),stackedWidget, SLOT(setCurrentIndex(int)));

	//setFixedHeight(800);
	//setFixedWidth(1200);
	setCentralWidget(stackedWidget);

	create_actions();
	create_toolbars();
}

MainWindow::~MainWindow()
{
    delete login_page;
    delete tuote;
    delete myynti;
    delete kayttajat;
	delete &login::singleton();
}

void
MainWindow::
show_card_dialog( login::read_rfid_status stat )
{
	if( stat == login::new_card )
	{
		saved_view = stackedWidget->currentIndex();
		emit stackedWidget->setCurrentIndex( 7 );
	}
	else if( stat == login::not_reading )
		emit stackedWidget->setCurrentIndex( saved_view );
}

void MainWindow::login()
{
	editToolBar->addAction(ToMainmenuAct);
	emit to_main_signal(1);
}

void MainWindow::logout()
{
	editToolBar->clear();
	emit to_main_signal(0);
}


void MainWindow::create_toolbars()
 {
	editToolBar = addToolBar(tr(""));
	editToolBar->setOrientation(Qt::Vertical);
	editToolBar->setFloatable(false);

}

void MainWindow::to_mainmenu()
 {
	if( login::singleton().interrupt_read_rfid() )
		emit logout();
	else
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
	db.setUserName("inventaari");
	db.setPassword("asdklielxkjoijdneidkod");
	if (!db.open()) {
	qDebug() << "Database error occurred";
	return false;
	}
	return true;
}

