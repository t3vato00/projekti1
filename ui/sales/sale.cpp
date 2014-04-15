#include "ui/sales/sale.h"
#include "ui_sale.h"
#include <QTableWidget>
#include <QTableView>
#include <QStringList>
#include <QString>
#include <QCompleter>



#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QDebug>

sale::sale(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sale)
{
    ui->setupUi(this);
    row_number=ostokset_yhteensa=0;
    tuote_hinta = 10;
    set_wordlist();
}

sale::~sale()
{
    delete ui;
}

void sale::set_wordlist(){

    QSqlQuery query;
    query.exec("select name from products");
    while (query.next())
        product_wordlist << query.value(0).toString();

}

void sale::on_pushButton_lisaa_tuote_clicked()
{

    ui->tableView_myynti_tuotteet->setRowHeight(row_number,100);

    if(row_number==0){
        QStringList headers;
        headers << "Tuotenimi" << "Tuotekoodi" << "Määrä" << "Hinta" << "Hinta yhteensä";
        for(int i=0; i<5;i++){
            ui->tableView_myynti_tuotteet->insertColumn(i);
            ui->tableView_myynti_tuotteet->setHorizontalHeaderItem(i, new QTableWidgetItem(headers.at(i)));
        }
    }
    ui->tableView_myynti_tuotteet->setColumnWidth(4,200);
    ui->tableView_myynti_tuotteet->insertRow(row_number);

    QTableWidgetItem* tuotenimi = new QTableWidgetItem;
    QTableWidgetItem* tuotekoodi = new QTableWidgetItem;
    QTableWidgetItem* tuotemaara = new QTableWidgetItem;
    QTableWidgetItem* tuotehinta = new QTableWidgetItem;
    QTableWidgetItem* tuotehinta_yhteensa = new QTableWidgetItem;


    int maara = ui->lineEdit_m_maara->displayText().toInt();
    int tuote_hinta_yhteensa= tuote_hinta* maara;

    tuotenimi->setText(ui->lineEdit_m_nimi->text());
    ui->tableView_myynti_tuotteet->setItem(row_number, 0, tuotenimi);

    tuotekoodi->setText(ui->lineEdit_m_koodi->text());
    ui->tableView_myynti_tuotteet->setItem(row_number, 1, tuotekoodi);

    tuotemaara->setText(ui->lineEdit_m_maara->text());
    ui->tableView_myynti_tuotteet->setItem(row_number, 2, tuotemaara);

    tuotehinta->setText(QString::number(tuote_hinta)+ " €");
    ui->tableView_myynti_tuotteet->setItem(row_number, 3, tuotehinta);

    tuotehinta_yhteensa->setText(QString::number(tuote_hinta_yhteensa)+ " €");
    ui->tableView_myynti_tuotteet->setItem(row_number, 4, tuotehinta_yhteensa);


    ostokset_yhteensa = ostokset_yhteensa+ tuote_hinta_yhteensa;
    ui->label_ostokset_yhteensa->setText(QString::number(ostokset_yhteensa) + " €");
    row_number++;
}

void sale::on_lineEdit_m_maara_textChanged(const QString &maara)
{

    int tuote_hinta_yhteensa= tuote_hinta* maara.toInt();
    ui->label_tuotehinta_yhteensa->setText(QString::number(tuote_hinta_yhteensa)+ " €");
}

void sale::on_lineEdit_m_nimi_textChanged(const QString &arg1)
{
    QCompleter *completer = new QCompleter(product_wordlist, this);
    completer->setCompletionMode(QCompleter::InlineCompletion);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit_m_nimi->setCompleter(completer);
}

void sale::on_lineEdit_m_nimi_editingFinished()
{
    ui->label_tuotehinta->setText(QString::number(tuote_hinta)+ " €");
}
