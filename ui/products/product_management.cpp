#include <QMessageBox>
#include <QSqlError>

#include <ui/products/product_management.h>
#include <db/utilities.h>
#include "ui_product_management.h"

product_management::
product_management(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::product_management),
	 insert()
{
	ui->setupUi(this);

	ui->productView->setModel(&model);
	filterTimer.setInterval(1000);
	filterTimer.setSingleShot(true);
	QObject::connect(ui->filterLine,&QLineEdit::textChanged,this,&product_management::update_filter);
	QObject::connect(&filterTimer,&QTimer::timeout,this,&product_management::refresh_view);
	refresh_view();

	insert.prepare("INSERT INTO products(code, name, price, stock) VALUES(?,?,?,?);");
	QObject::connect(ui->addCode,&QLineEdit::textChanged,this,&product_management::add_code_changed);
	add_code_changed();
	QObject::connect(ui->addName,&QLineEdit::textChanged,this,&product_management::add_name_changed);
	add_name_changed();
	QObject::connect(ui->addPrice,&QLineEdit::textChanged,this,&product_management::add_price_changed);
	add_price_changed();
	QObject::connect(ui->addStock,&QLineEdit::textChanged,this,&product_management::add_stock_changed);
	add_stock_changed();
}

product_management::
~product_management()
{
	delete ui;
}

void
product_management::
update_filter()
{
	if( model.setSearchString(ui->filterLine->text()) )
	{
		ui->filterLine->setStyleSheet(".QLineEdit { background: blue; }");
		filterTimer.start();
	}
	else
	{
		ui->filterLine->setStyleSheet(".QLineEdit { background: red; }");
		filterTimer.stop();
	}
}

void
product_management::
refresh_view()
{
	filterTimer.stop();
	model.refresh();
	ui->filterLine->setStyleSheet("");
	emit ui->productView->resizeColumnsToContents();
}

void
product_management::
add_code_changed()
{
	QString code = normalize_string_input(ui->addCode->text());
	if( (add_code_valid = product::check_barcode(code)) )
	{
		ui->addCode->setStyleSheet("");
		add_code = code;
	}
	else
	{
		ui->addCode->setStyleSheet(".QLineEdit { background: red; }");
		add_code = QStringLiteral("");
	}
}

void
product_management::
add_name_changed()
{
	QString name = normalize_string_input(ui->addName->text());
	if( (add_name_valid = name.length() > 0 && name.length() <= 200) )
	{
		ui->addName->setStyleSheet("");
		add_name = name;
	}
	else
	{
		ui->addName->setStyleSheet(".QLineEdit { background: red; }");
		add_name = QStringLiteral("");
	}
}

void
product_management::
add_price_changed()
{
	bool ok;
	double price = normalize_string_input(ui->addPrice->text()).toDouble(&ok);
	if( (add_price_valid = ok && price >= 0.0) )
	{
		ui->addPrice->setStyleSheet("");
		add_price = price;
	}
	else
	{
		ui->addPrice->setStyleSheet(".QLineEdit { background: red; }");
		add_price = 0.0;
	}
}

void
product_management::
add_stock_changed()
{
	bool ok;
	unsigned stock = normalize_string_input(ui->addStock->text()).toUInt(&ok);
	if( (add_stock_valid = ok) )
	{
		ui->addStock->setStyleSheet("");
		add_stock = stock;
	}
	else
	{
		ui->addStock->setStyleSheet(".QLineEdit { background: red; }");
		add_stock = 0.0;
	}
}

void
product_management::
add_product()
{
	if(!add_code_valid)
	{
		critical_error( "Invalid barcode." );
		return;
	}
	if(!add_name_valid)
	{
		critical_error( "Invalid name." );
		return;
	}
	if(!add_price_valid)
	{
		critical_error( "Invalid price." );
		return;
	}
	if(!add_stock_valid)
	{
		critical_error( "Invalid stock amount." );
		return;
	}

	insert.bindValue(0,add_code);
	insert.bindValue(1,add_name);
	insert.bindValue(2,add_price);
	insert.bindValue(3,add_stock);
	if(!insert.exec())
		database_error( insert.lastError() );
	insert.finish();
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

