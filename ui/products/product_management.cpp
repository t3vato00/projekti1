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

	ui->product_view->setModel(&model);
	ui->product_view->setSelectionBehavior(QAbstractItemView::SelectRows);
	filter_timer.setInterval(1500);
	filter_timer.setSingleShot(true);
	QObject::connect(ui->filter_line, &QLineEdit::textChanged, this, &product_management::update_filter);
	QObject::connect(&filter_timer, &QTimer::timeout, this, &product_management::refresh_view);
	QObject::connect(ui->filter_refresh, &QPushButton::clicked, this, &product_management::refresh_view);
	QObject::connect(ui->delete_button, &QPushButton::clicked, this, &product_management::delete_products);
	update_filter();
	refresh_view();

    insert.prepare("INSERT INTO products(code, name, price, stock, description) VALUES(?,?,?,?,?);");
	QObject::connect(ui->add_code, &QLineEdit::textChanged, this, &product_management::add_code_changed);
	add_code_changed();
	QObject::connect(ui->add_name, &QLineEdit::textChanged, this, &product_management::add_name_changed);
	add_name_changed();
	QObject::connect(ui->add_price, &QLineEdit::textChanged, this, &product_management::add_price_changed);
	add_price_changed();
	QObject::connect(ui->add_stock, &QLineEdit::textChanged, this, &product_management::add_stock_changed);
	add_stock_changed();
	QObject::connect(ui->add_button, &QPushButton::clicked, this, &product_management::add_product);
	QObject::connect(ui->clear_add, &QPushButton::clicked, this, &product_management::clear_add);
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
	if( model.setSearchString(ui->filter_line->text()) )
	{
		ui->filter_line->setStyleSheet(".QLineEdit { background: blue; }");
		filter_timer.start();
	}
	else
	{
		ui->filter_line->setStyleSheet(".QLineEdit { background: red; }");
		filter_timer.stop();
	}
}

void
product_management::
refresh_view()
{
	filter_timer.stop();
	model.refresh();
	ui->filter_line->setStyleSheet("");
	emit ui->product_view->resizeColumnsToContents();
}

void
product_management::
add_code_changed()
{
	QString code = normalize_string_input(ui->add_code->text());
	if( (add_code_valid = product::check_barcode(code)) )
	{
		ui->add_code->setStyleSheet("");
		add_code = code;
	}
	else
	{
		ui->add_code->setStyleSheet(".QLineEdit { background: red; }");
		add_code = QStringLiteral("");
	}
}

void
product_management::
add_name_changed()
{
	QString name = normalize_string_input(ui->add_name->text());
	if( (add_name_valid = name.length() > 0 && name.length() <= 200) )
	{
		ui->add_name->setStyleSheet("");
		add_name = name;
	}
	else
	{
		ui->add_name->setStyleSheet(".QLineEdit { background: red; }");
		add_name = QStringLiteral("");
	}
}

void
product_management::
add_price_changed()
{
	bool ok;
	double price = normalize_string_input(ui->add_price->text()).toDouble(&ok);
	if( (add_price_valid = ok && price >= 0.0) )
	{
		ui->add_price->setStyleSheet("");
		add_price = price;
	}
	else
	{
		ui->add_price->setStyleSheet(".QLineEdit { background: red; }");
		add_price = 0.0;
	}
}

void
product_management::
add_stock_changed()
{
	bool ok;
	unsigned stock = normalize_string_input(ui->add_stock->text()).toUInt(&ok);
	if( (add_stock_valid = ok) )
	{
		ui->add_stock->setStyleSheet("");
		add_stock = stock;
	}
	else
	{
		ui->add_stock->setStyleSheet(".QLineEdit { background: red; }");
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
    insert.bindValue(4,ui->add_desc->text());
	if(!insert.exec())
		database_error( insert.lastError() );
	insert.finish();
	refresh_view();
}

void
product_management::
clear_add()
{
	ui->add_code->setText(QStringLiteral(""));
	ui->add_name->setText(QStringLiteral(""));
	ui->add_price->setText(QStringLiteral(""));
	ui->add_stock->setText(QStringLiteral(""));
}

void
product_management::
delete_products()
{
	auto selection = ui->product_view->selectionModel()->selectedRows(0);
	for( auto index : selection )
		this->model.removeRow( index.row(), index.parent());
}

