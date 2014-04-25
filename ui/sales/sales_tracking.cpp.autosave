#include "sales_tracking.h"
#include "ui_sales_tracking.h"
#include "db/products/product.h"
#include <QAbstractItemView>

sales_tracking::sales_tracking(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sales_tracking)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this);
    model->setTable("sales_event");
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Seller card number"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Total sum"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
    refresh_timer = new QTimer(this);
    refresh_timer->setInterval(1000);
    refresh_timer->start();
    QObject::connect(refresh_timer, SIGNAL(timeout()), this, SLOT(update_view()));
}

sales_tracking::~sales_tracking()
{
    delete ui;
    delete refresh_timer;
    delete model;
}

void sales_tracking::update_view()
{
    refresh_timer->setInterval(10000);
    model->select();
    ui->tableView_sales_event->setModel(model);
    ui->tableView_sales_event->hideColumn(0);
    ui->tableView_sales_event->resizeColumnsToContents();
    ui->tableView_sales_event->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void sales_tracking::on_pushButton_clicked()
{
    int selected = ui->tableView_sales_event->selectionModel()->currentIndex().row();
    QModelIndex index = model->index(selected, 0, QModelIndex());
    QString sales_event_id = ui->tableView_sales_event->model()->data(index).toString();

    row_model = new QSqlQueryModel;
    row_model->setQuery("SELECT * FROM sales_row INNER JOIN products ON sales_row.product_code = products.code WHERE event_id = "+sales_event_id);
    ui->tableView_sales_row->setModel(row_model);

    ui->tableView_sales_row->hideColumn(0);
    ui->tableView_sales_row->hideColumn(1);
    ui->tableView_sales_row->hideColumn(4);
    ui->tableView_sales_row->hideColumn(7);

    row_model->setHeaderData(2, Qt::Horizontal, QObject::tr("Product code"));
    row_model->setHeaderData(3, Qt::Horizontal, QObject::tr("Amount"));
    row_model->setHeaderData(5, Qt::Horizontal, QObject::tr("Product name"));
    row_model->setHeaderData(6, Qt::Horizontal, QObject::tr("Product price"));
    ui->tableView_sales_row->resizeColumnsToContents();

}
