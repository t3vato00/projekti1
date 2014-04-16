#ifndef HEADER_DB_PRODUCT_MODEL
#define HEADER_DB_PRODUCT_MODEL

#include <QSortFilterProxyModel>
#include <QSqlQueryModel>

class product_model : public QSortFilterProxyModel
{
public:
	product_model(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());

private:
	QSqlQueryModel impl;
};

#endif // HEADER_DB_PRODUCT_MODEL

