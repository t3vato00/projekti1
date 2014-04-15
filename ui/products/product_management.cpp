#include "product_management.h"
#include "ui_product_management.h"

product_management::
product_management(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::product_management)
{
	ui->setupUi(this);
}

product_management::
~product_management()
{
	delete ui;
}

void
product_management::
add_product()
{
}

void
product_management::
clear_add()
{
	ui->addCode->setText(QStringLiteral(""));
	ui->addName->setText(QStringLiteral(""));
	ui->addPrice->setText(QStringLiteral(""));
	ui->addStock->setText(QStringLiteral(""));
}

void
product_management::
update_filter()
{
}

void
product_management::
clear_filter()
{
	ui->filterCode->setText(QStringLiteral(""));
	ui->filterName->setText(QStringLiteral(""));
	ui->filterPrice->setText(QStringLiteral(""));
	ui->filterStock->setText(QStringLiteral(""));
	update_filter();
}

