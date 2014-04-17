#ifndef HEADER_DB_PRODUCT_MODEL
#define HEADER_DB_PRODUCT_MODEL

#include <QAbstractTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <vector>

#include <db/products/product.h>

class product_model : public QAbstractTableModel
{
	Q_OBJECT

public:
	product_model(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());
	~product_model();

	virtual int rowCount( const QModelIndex & parent = QModelIndex() ) const;
	virtual int columnCount( const QModelIndex & parent = QModelIndex() ) const;
	//virtual QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
	virtual QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const;
	virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
	virtual void sort( int column, Qt::SortOrder order = Qt::AscendingOrder );

	virtual bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
	virtual Qt::ItemFlags flags( const QModelIndex & index ) const;

	bool setSearchString( QString const & str );

public slots:
	void refresh();

private:
	struct product_item : public product
	{
		inline product_item(QString code, QString name, double price, int stock)
		: product(code,name,price,stock)
		{
		}

		bool name_changed = false;
		bool price_changed = false;
		bool stock_changed = false;
	};

	unsigned sort_column;
	QSqlDatabase db;
	std::vector<product_item *> _data;

	bool row_dissapeared( int row );

	QSqlQuery query;
	QSqlQuery sql_ch_code;
	QSqlQuery sql_sl_name;
	QSqlQuery sql_ch_name;
	QSqlQuery sql_sl_price;
	QSqlQuery sql_ch_price;
	QSqlQuery sql_sl_stock;
	QSqlQuery sql_ch_stock;
};

#endif // HEADER_DB_PRODUCT_MODEL

