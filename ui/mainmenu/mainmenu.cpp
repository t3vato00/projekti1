#include "ui/mainmenu/mainmenu.h"
#include "ui_mainmenu.h"
#include <QSignalMapper>

mainmenu::mainmenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainmenu)
{
    ui->setupUi(this);

    QSignalMapper* signalMapper = new QSignalMapper (this) ;
    QObject::connect(ui->pushButton_myynti, SIGNAL(clicked()), signalMapper, SLOT(map()));
    QObject::connect(ui->pushButton_product, SIGNAL(clicked()), signalMapper, SLOT(map()));
    QObject::connect(ui->pushButton_kt_hallinta, SIGNAL(clicked()), signalMapper, SLOT(map()));
    QObject::connect(ui->pushButton_salestrack, SIGNAL(clicked()), signalMapper, SLOT(map()));
    QObject::connect(ui->pushButton_selling, SIGNAL(clicked()),signalMapper,SLOT(map()));

    signalMapper -> setMapping (ui->pushButton_myynti, 3);
    signalMapper -> setMapping (ui->pushButton_product, 2);
    signalMapper -> setMapping (ui->pushButton_kt_hallinta, 4);
    signalMapper -> setMapping (ui->pushButton_salestrack, 5);
    signalMapper -> setMapping (ui->pushButton_selling,6);

    connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(send_page(int))) ;
}

mainmenu::~mainmenu()
{
    delete ui;
}
void mainmenu::send_page(int page_index)
{
    emit send_page_index(page_index);
}
