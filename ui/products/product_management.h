#ifndef PRODUCT_MANAGEMENT_H
#define PRODUCT_MANAGEMENT_H

#include <QTimer>
#include <QWidget>
#include <QSqlQuery>
#include <QPushButton>
#include <db/products/product_model.h>

namespace Ui {
class product_management;
}

class product_management : public QWidget
{
	Q_OBJECT

public:
	explicit product_management(QWidget *parent = 0);
	~product_management();

private slots:
	void add_product();
	void clear_add();
	void update_filter();
	void refresh_view();
	void delete_products();
	void add_code_changed();
	void add_name_changed();
	void add_price_changed();
	void add_stock_changed();

private:
	QTimer filter_timer;
	Ui::product_management *ui;
	product_model model;
	QSqlQuery insert;

	bool add_code_valid;
	QString add_code;

	bool add_name_valid;
	QString add_name;

	bool add_price_valid;
	double add_price;

	bool add_stock_valid;
	unsigned add_stock;
};

#endif // PRODUCT_MANAGEMENT_H
