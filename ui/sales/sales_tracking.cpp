#include "sales_tracking.h"
#include "ui_sales_tracking.h"
#include "db/products/product.h"
sales_tracking::sales_tracking(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sales_tracking)
{
    ui->setupUi(this);
}

sales_tracking::~sales_tracking()
{
    delete ui;
}
