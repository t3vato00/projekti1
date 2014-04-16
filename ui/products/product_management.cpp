#include <QMessageBox>
#include <QSqlError>
#include "product_management.h"
#include "ui_product_management.h"
#include "../db/products/product.h"

product_management::
product_management(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::product_management),
	 insert()
{
	ui->setupUi(this);
	ui->productView->setModel(&model);
	insert.prepare("INSERT INTO products(code, name, price, stock) VALUES(?,?,?,?);");
}

product_management::
~product_management()
{
	delete ui;
}

inline
QString
normalize_string_input( QString const & q )
{
	return q.normalized(QString::NormalizationForm_C).trimmed();
}

void invalid_value( QString const msg )
{
	QMessageBox msgb;

	msgb.setText(msg);
	msgb.setIcon(QMessageBox::Critical);
	msgb.exec();
}

void database_error( QString const msg )
{
	QMessageBox msgb;

	msgb.setText(msg);
	msgb.setIcon(QMessageBox::Critical);
	msgb.exec();
}

void
product_management::
add_product()
{
	bool ok;
	QString code = normalize_string_input(ui->addCode->text());
	QString name = normalize_string_input(ui->addName->text());
	QString priceStr = normalize_string_input(ui->addPrice->text());
	QString stockStr = normalize_string_input(ui->addStock->text());
    if(!product::check_barcode(code))
	{
		invalid_value( "Invalid code '" + code + "'." );
		return;
	}
	double price = priceStr.toDouble(&ok);
	if(!ok)
	{
		invalid_value( "Invalid price '" + priceStr + "'." );
		return;
	}
	unsigned stock = priceStr.toUInt(&ok);
	if(!ok)
	{
		invalid_value( "Invalid stock amount '" + stockStr + "'." );
		return;
	}

	insert.bindValue(0,code);
	insert.bindValue(1,name);
	insert.bindValue(2,price);
	insert.bindValue(3,stock);
	ok = insert.exec();

	if(!ok)
		database_error( "Database error: " + insert.lastError().text() );
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

