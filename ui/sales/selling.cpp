#include "selling.h"
#include "ui_selling.h"

Selling::Selling(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Selling)
{

    ui->setupUi(this);
    row_Amount = 0;
    QStringList Headers;
    Headers << "Nimi" << "Hinta";
    QObject::connect(ui->tableWidgetProducts,SIGNAL(cellClicked(int,int)),this,SLOT(modified(int,int)));

    for(int k=0;k<2;k++)
    {
        ui->tableWidgetProducts->insertColumn(k);
        ui->tableWidgetProducts->setHorizontalHeaderLabels(Headers);
        ui->tableWidgetProducts->setColumnWidth(k,74);
    }
    load_products();
}

void Selling::load_products()
{
    products.prepare("SELECT name, price FROM products;");
    products.exec();
    while(products.next())
    {
        add_row_to_list(products.value(0).toString(),products.value(1).toString());
    }
    products.finish();
}
void Selling::add_row_to_list(QString nimi, QString hinta)
{
    ui->tableWidgetProducts->insertRow(row_Amount);
    QTableWidgetItem* userNimi = new QTableWidgetItem;
    QTableWidgetItem* userHinta = new QTableWidgetItem;

    userNimi->setText(nimi);
    userHinta->setText(hinta);
    userNimi->setTextAlignment(Qt::AlignCenter);
    userHinta->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetProducts->setItem(row_Amount,0,userNimi);
    ui->tableWidgetProducts->setItem(row_Amount,1,userHinta);
}

void Selling::modified(int a, int b)
{
    qDebug() << a << b;
    cell.prepare("SELECT * from products");
    cell.exec();
}

Selling::~Selling()
{
    delete ui;
}
