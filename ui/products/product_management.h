#ifndef PRODUCT_MANAGEMENT_H
#define PRODUCT_MANAGEMENT_H

#include <QWidget>
#include <QSqlQuery>
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
	void clear_filter();

private:
	Ui::product_management *ui;
	product_model model;
	QSqlQuery insert;
};

#endif // PRODUCT_MANAGEMENT_H
