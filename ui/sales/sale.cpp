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
#include <QMessageBox>

#include <QtSql>
#include <QDebug>
#include <QSqlError>

sale::sale(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sale)
{
    ui->setupUi(this);
    row_number=total_price=product_price = 0;
    set_wordlist();
    new_product = new product();
    sales_row = new QSqlQueryModel;
    disable_all();
}

sale::~sale()
{
    delete ui;
    delete new_product;
    if(sales_row)
    delete sales_row;
}

void sale::on_b_delete_row_clicked()
{
    int selected = ui->salelist->selectionModel()->currentIndex().row();
    QModelIndex index = sales_row->index(selected, 0, QModelIndex());
    QModelIndex amount_index = sales_row->index(selected, 3, QModelIndex());
    QModelIndex product_index = sales_row->index(selected, 2, QModelIndex());

    QString row_id = ui->salelist->model()->data(index).toString();
    QString product_code = ui->salelist->model()->data(product_index).toString();
    int amount_ind = ui->salelist->model()->data(amount_index).toInt();
    delete_row(row_id,product_code,amount_ind);

}
void sale::on_new_event_clicked()
{

    QString card_number = "pekka";
    QSqlQuery querys;
    querys.prepare("INSERT INTO sales_event VALUES(Null,?,?,NOW()); SELECT LAST_INSERT_ID();");
    querys.bindValue(0,card_number);
    querys.bindValue(1,QString::number( total_price, 'f', 2 ));
    querys.exec();

    if(querys.nextResult() ){
        if( querys.next())
            sale_event_id = querys.value(0).toInt();
    }
    querys.finish();
    refresh_list();
    enable_all();
}

void sale::on_b_delete_all_clicked()
{
    int rows = ui->salelist->verticalHeader()->count();
    for(int i=0;i<rows;i++){
        QModelIndex amount_index = sales_row->index(i, 3, QModelIndex());
        QModelIndex product_index = sales_row->index(i, 2, QModelIndex());

        int amount = ui->salelist->model()->data(amount_index).toInt();
        QString product_code = ui->salelist->model()->data(product_index).toString();
        delete_row(0,product_code,amount);
        qDebug() << "deleted rows " << rows;
        qDebug() << "amounts" << amount;
    }

    QSqlQuery delete_event;
    delete_event.prepare("DELETE FROM sales_event WHERE sales_event_id = ?");
    delete_event.bindValue(0,sale_event_id);
    delete_event.exec();
    delete_event.finish();
    refresh_list();
    disable_all();
    clear_lineEdits();
}

void sale::on_product_name_editingFinished()
{
    if(ui->product_name->text() != ""){
        if(current_product_name != ui->product_name->text()){

            current_product_name = ui->product_name->text();
            new_product->set_by_name(current_product_name);
            ui->product_code->setText(new_product->barcode());
            ui->label_tuotehinta->setText(QString::number(new_product->price())+ " €");
            ui->label_stock->setText(QString::number(new_product->stock()));
            product_price = new_product->price();
            stock_amount = new_product->stock();
        }
    }else{
        clear_lineEdits();
        current_product_name = "";
    }
}

void sale::on_b_clear_clicked()
{
     clear_lineEdits();
}

void sale::on_b_add_clicked()
{
    if(stock_amount >= ui->product_amount->text().toInt())
    {
        QSqlQuery query;
        query.prepare("INSERT INTO sales_row VALUES(Null,?,?,?);UPDATE products SET stock=stock-? WHERE code = ?");
        query.bindValue(0,sale_event_id);
        query.bindValue(1,ui->product_code->text());
        query.bindValue(2,ui->product_amount->text().toInt());
        query.bindValue(3,ui->product_amount->text().toInt());
        query.bindValue(4,ui->product_code->text());
        query.exec();
        query.finish();

        refresh_total_sum();
        clear_lineEdits();
    }
    refresh_list();
    current_product_name = "";
}

void sale::on_product_name_textChanged(const QString &arg1)
{
    QCompleter *completer = new QCompleter(product_wordlist, this);
    completer->setCompletionMode(QCompleter::InlineCompletion);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->product_name->setCompleter(completer);
}

void sale::on_product_amount_textChanged(const QString &maara)
{
    int tuote_hinta_yhteensa= product_price* maara.toInt();
    ui->label_tuotehinta_yhteensa->setText(QString::number(tuote_hinta_yhteensa)+ " €");
    if(stock_amount <= ui->product_amount->text().toInt())
        ui->product_amount->setStyleSheet(".QLineEdit { background: red; }");
    else
        ui->product_amount->setStyleSheet("");
}

void sale::on_b_sell_clicked()
{
    QSqlQuery querys;
    querys.prepare("UPDATE sales_event SET total_sum = ? WHERE sales_event_id = ?;");
    querys.bindValue(0,ui->label_ostokset_yhteensa->text());
    querys.bindValue(1,sale_event_id);
    querys.exec();
    querys.finish();

    delete sales_row;
    sales_row = NULL;
    //sale_event_id = NULL;
    disable_all();
    clear_lineEdits();
    refresh_total_sum();
}
/************************/
// funktiot
/************************/
void sale::set_wordlist(){

    QSqlQuery query;
    query.exec("select name from products");
    while (query.next())
        product_wordlist << query.value(0).toString();
    query.finish();
}

void sale::clear_lineEdits()
{
    ui->product_name->setText(QStringLiteral(""));
    ui->product_code->setText(QStringLiteral(""));
    ui->product_amount->setText(QStringLiteral(""));
    ui->label_stock->setText("0");
    ui->label_tuotehinta->setText(QStringLiteral("0"));
    ui->label_tuotehinta_yhteensa->setText(QStringLiteral("0"));
}

void sale::disable_all()
{
    ui->product_name->setDisabled(true);
    ui->product_code->setDisabled(true);
    ui->product_amount->setDisabled(true);
    ui->b_clear->setDisabled(true);
    ui->b_add->setDisabled(true);
    ui->b_delete_row->setDisabled(true);
    ui->b_delete_all->setDisabled(true);
    ui->b_sell->setDisabled(true);
}

void sale::enable_all()
{

    ui->product_name->setEnabled(true);
    ui->product_code->setEnabled(true);
    ui->product_amount->setEnabled(true);
    ui->b_clear->setEnabled(true);
    ui->b_add->setEnabled(true);
    ui->b_delete_row->setEnabled(true);
    ui->b_delete_all->setEnabled(true);
    ui->b_sell->setEnabled(true);
}

void sale::refresh_list()
{

    sales_row->setQuery("SELECT * FROM sales_row INNER JOIN products ON sales_row.product_code = products.code WHERE event_id = "+QString::number(sale_event_id));
    ui->salelist->setModel(sales_row);

    ui->salelist->hideColumn(0);
    ui->salelist->hideColumn(1);
    ui->salelist->hideColumn(4);
    ui->salelist->hideColumn(7);

    sales_row->setHeaderData(2, Qt::Horizontal, QObject::tr("Product code"));
    sales_row->setHeaderData(3, Qt::Horizontal, QObject::tr("Amount"));
    sales_row->setHeaderData(5, Qt::Horizontal, QObject::tr("Product name"));
    sales_row->setHeaderData(6, Qt::Horizontal, QObject::tr("Product price"));
    ui->salelist->resizeColumnsToContents();

}
void sale::delete_row(QString row_id, QString p_code, int amount)
{
    QSqlQuery query;
    query.prepare("DELETE FROM sales_row WHERE row_id = ?;UPDATE products SET stock = stock+? WHERE code=?;");
    query.bindValue(0,row_id);
    query.bindValue(1,amount);
    query.bindValue(2,p_code);
    query.exec();
    query.finish();

    refresh_list();
}

void sale::refresh_total_sum()
{
    QSqlQuery querys;
    querys.prepare("SELECT sum(amount*price) FROM sales_row INNER JOIN products ON sales_row.product_code = products.code WHERE event_id = ?;");
    querys.bindValue(0,sale_event_id);
    querys.exec();
    QString total_sum;
    if( querys.next())
        total_sum = querys.value(0).toString();
    querys.finish();

    ui->label_ostokset_yhteensa->setText(total_sum);
}
