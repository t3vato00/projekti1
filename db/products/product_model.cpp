
#include <db/products/product_model.h>

product_model::
product_model(QObject * parent, QSqlDatabase db)
: impl( parent )
{
	impl.setQuery(QStringLiteral("SELECT code, name, price, stock FROM products;"));
	impl.setHeaderData(0, Qt::Horizontal, tr("code"));
	impl.setHeaderData(1, Qt::Horizontal, tr("name"));
	impl.setHeaderData(2, Qt::Horizontal, tr("price"));
	impl.setHeaderData(3, Qt::Horizontal, tr("stock"));
	setSourceModel(&impl);
}

