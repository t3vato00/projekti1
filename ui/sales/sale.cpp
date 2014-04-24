#include "ui/sales/sale.h"
#include "db/sales/sales_row.h"
#include "ui_sale.h"
#include <QTableWidget>
#include <QTableView>
#include <QString>
#include <QCompleter>
#include <QVector>
#include <QDateTime>
#include <qvariant.h>

#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QSqlError>

sale::sale(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sale)
{
    ui->setupUi(this);
    row_number=total_price=product_price =0;
    set_wordlist();

    ui->tableView_myynti_tuotteet->setRowHeight(row_number,100);

    QStringList headers;
    headers << "Tuotenimi" << "Tuotekoodi" << "Määrä" << "Hinta" << "Hinta yhteensä";
    for(int i=0; i<5;i++){
        ui->tableView_myynti_tuotteet->insertColumn(i);
        ui->tableView_myynti_tuotteet->setColumnWidth(i,200);
    }
    ui->tableView_myynti_tuotteet->setHorizontalHeaderLabels(headers);
    new_product = new product();

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
    query.finish();
}

void sale::on_pushButton_lisaa_tuote_clicked()
{
    ui->tableView_myynti_tuotteet->insertRow(row_number);

    QTableWidgetItem* tuotenimi = new QTableWidgetItem;
    QTableWidgetItem* tuotekoodi = new QTableWidgetItem;
    QTableWidgetItem* tuotemaara = new QTableWidgetItem;
    QTableWidgetItem* tuotehinta = new QTableWidgetItem;
    QTableWidgetItem* tuotehinta_yhteensa = new QTableWidgetItem;


    int maara = ui->lineEdit_m_maara->displayText().toInt();
    int product_total_price = product_price* maara;
    total_price = total_price+ product_total_price;

    tuotenimi->setText(ui->lineEdit_m_nimi->text());
    tuotekoodi->setText(ui->lineEdit_m_koodi->text());
    tuotemaara->setText(ui->lineEdit_m_maara->text());
    tuotehinta->setText(QString::number(product_price)+ " €");
    tuotehinta_yhteensa->setText(QString::number(product_total_price)+ " €");

    ui->tableView_myynti_tuotteet->setItem(row_number, 0, tuotenimi);
    ui->tableView_myynti_tuotteet->setItem(row_number, 1, tuotekoodi);
    ui->tableView_myynti_tuotteet->setItem(row_number, 2, tuotemaara);
    ui->tableView_myynti_tuotteet->setItem(row_number, 3, tuotehinta);
    ui->tableView_myynti_tuotteet->setItem(row_number, 4, tuotehinta_yhteensa);
    ui->label_ostokset_yhteensa->setText(QString::number(total_price) + " €");

    add_row_to_list();
    clear_lineEdits();
    row_number++;
    current_product_name = "";
}

void sale::add_row_to_list()
{
    int sale_id=1;
    sales_row new_row =  sales_row( sale_id,
                                        ui->lineEdit_m_koodi->text(),
                                        ui->lineEdit_m_maara->text().toDouble()
                                       );
    sales_list.append(new_row);
}

void sale::on_lineEdit_m_maara_textChanged(const QString &maara)
{

    int tuote_hinta_yhteensa= product_price* maara.toInt();
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


    if(ui->lineEdit_m_nimi->text() != ""){
        if(current_product_name != ui->lineEdit_m_nimi->text()){

            current_product_name = ui->lineEdit_m_nimi->text();
            new_product->set_by_name(current_product_name);

            product_price = new_product->price();
            ui->lineEdit_m_koodi->setText(new_product->barcode());
            ui->label_tuotehinta->setText(QString::number(new_product->price())+ " €");
        }
    }else{
        clear_lineEdits();
        current_product_name = "";
    }
}

void sale::clear_lineEdits()
{
    ui->lineEdit_m_nimi->setText(QStringLiteral(""));
    ui->lineEdit_m_koodi->setText(QStringLiteral(""));
    ui->lineEdit_m_maara->setText(QStringLiteral(""));
    ui->label_tuotehinta->setText(QStringLiteral("0"));
    ui->label_tuotehinta_yhteensa->setText(QStringLiteral("0"));
}

void sale::on_lineEdit_clear_clicked()
{
    clear_lineEdits();
}

void sale::on_myy_clicked()
{
    QString card_number = "kortinnum";
    QSqlQuery querys;
    querys.prepare("INSERT INTO sales_event VALUES(Null,?,?,NOW()); SELECT LAST_INSERT_ID();");
    querys.bindValue(0,card_number);
    querys.bindValue(1,QString::number( total_price, 'f', 2 ));
    querys.exec();
    querys.finish();

    int id;
    if(querys.nextResult() ){
        if( querys.next())
            id = querys.value(0).toInt();
    }
    qDebug() << querys.isActive();


    for (auto i = sales_list.begin(); i != sales_list.end(); ++i){
        bool can_sell = false;
        QSqlDatabase::database().transaction();
        QSqlQuery sql_myy;
        sql_myy.prepare("UPDATE products SET stock=stock-? WHERE code = ?;"
                        "SELECT stock FROM products WHERE code=?;"
                        "INSERT INTO sales_row VALUES(null,?,?,?);");

        sql_myy.bindValue(0,(*i).amount);
        sql_myy.bindValue(1,(*i).product_code);

        sql_myy.bindValue(2,(*i).product_code);

        sql_myy.bindValue(3,id);
        sql_myy.bindValue(4,(*i).product_code);
        sql_myy.bindValue(5,QString::number((*i).amount,'f',2));
        sql_myy.exec();

        if(sql_myy.nextResult()){
            if(sql_myy.next()){
                qDebug() << sql_myy.value(0).toInt();
                if(sql_myy.value(0).toInt()>=0)
                   can_sell = true;
            }
        }
        sql_myy.finish();
        if (can_sell)
        {
            QSqlDatabase::database().commit();
            qDebug() << "commit called!!";
        }
        else
        {
            QSqlDatabase::database().rollback();
            qDebug() << "rollback called!!";
        }

        /*
        lisaa.prepare("INSERT INTO sales_row VALUES(null,?,?,?);");
        lisaa.bindValue(2,id);
        lisaa.bindValue(3,(*i).product_code);
        lisaa.bindValue(4,QString::number((*i).amount,'f',2));
        lisaa.exec();*/


    }
}
