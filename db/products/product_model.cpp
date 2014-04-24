#include <QSqlError>
#include <db/products/product_model.h>
#include <db/utilities.h>
#include <QDebug>
#include <QBrush>

enum pmcolumn : unsigned
{ pmcolcode = 0
, pmcolname
, pmcolprice
, pmcolstock
, pmcolsize
};

product_model::
product_model(QObject * parent, QSqlDatabase db)
: QAbstractTableModel(parent), sort_column(pmcolname), db(db), query(db)
, sql_ch_code(QStringLiteral("UPDATE products SET code = ? WHERE code = ?;"), db)
, sql_sl_name(QStringLiteral("SELECT name FROM products WHERE code = ?;"), db)
, sql_ch_name(QStringLiteral("UPDATE products SET name = ? WHERE code = ? AND name = ?;"), db)
, sql_sl_price(QStringLiteral("SELECT price FROM products WHERE code = ?;"), db)
, sql_ch_price(QStringLiteral("UPDATE products SET price = ? WHERE code = ? AND price = ?;"), db)
, sql_sl_stock(QStringLiteral("SELECT stock FROM products WHERE code = ?;"), db)
, sql_ch_stock(QStringLiteral("UPDATE products SET stock = ? WHERE code = ? AND stock = ?;"), db)
{
}

product_model::
~product_model()
{
	for( auto prod : _data )
		delete prod;
}

int
product_model::
rowCount( const QModelIndex & parent ) const
{
	if( parent.isValid() )
		return 0;
	else
		return _data.size();
}

int
product_model::
columnCount( const QModelIndex & parent ) const
{
	if( parent.isValid() )
		return 0;
	else
		return static_cast<int>(pmcolsize);
}

QVariant
product_model::
data( const QModelIndex & index, int role ) const
{
	if( index.parent().isValid() )
		return QVariant();

	unsigned row = index.row();
	if( row >= _data.size() )
		return QVariant();

	int column = index.column();
	QBrush changed(QColor(255,255,0));
	switch(role)
	{
	case Qt::DisplayRole:
	case Qt::EditRole:
		switch(column)
		{
		case pmcolcode: return _data[row]->barcode();
		case pmcolname: return _data[row]->name();
		case pmcolprice: return _data[row]->price();
		case pmcolstock: return _data[row]->stock();
		}
	case Qt::BackgroundRole:
		switch(column)
		{
		case pmcolname: return _data[row]->name_changed ? changed : QVariant();
		case pmcolprice: return _data[row]->price_changed ? changed : QVariant();
		case pmcolstock: return _data[row]->stock_changed ? changed : QVariant();
		}
	}

	return QVariant();
}

bool
product_model::
row_dissapeared( int row )
{
	qDebug() << "Row dissapeared!";
	beginRemoveRows(QModelIndex(),row,row);
	_data.erase(_data.begin()+row);
	endRemoveRows();
	return true;
}

bool
product_model::
setData( const QModelIndex & index, const QVariant & value, int role )
{
	if( index.parent().isValid() )
		return false;

	unsigned row = index.row();
	if( row >= _data.size() )
		return false;

	int column = index.column();
	switch(role)
	{
	case Qt::EditRole:
	case PretendSetRole:
		switch(column)
		{
		case pmcolcode:
			{
				QString oldcode = _data[row]->barcode();
				QString newcode = normalize_string_input(value.toString());
				if( oldcode == newcode )
					return true;
				if( !product::check_barcode(newcode) )
					return false;
				if( role == PretendSetRole )
					return true;

				sql_ch_code.bindValue(0,newcode);
				sql_ch_code.bindValue(1,oldcode);
				if( !sql_ch_code.exec() )
				{
					database_error( sql_ch_code.lastError() );
					return false;
				}
				if( sql_ch_code.numRowsAffected() == 0 ) return row_dissapeared(row);
				_data[row]->set_barcode(newcode);
				emit dataChanged( index, index );
				return true;
			}

		case pmcolname:
			{
				auto oldname = _data[row]->name();
				auto newprename = product::preprocess_name(value.toString());
				if( !product::check_name(newprename) )
					return false;
				auto newname = product::parse_name(newprename);
				if( oldname == newname )
					return true;
				if( role == PretendSetRole )
					return true;

				sql_ch_name.bindValue(0,newname);
				sql_ch_name.bindValue(1,_data[row]->barcode());
				sql_ch_name.bindValue(2,oldname);
				if( !sql_ch_name.exec() )
				{
					database_error( sql_ch_name.lastError() );
					return false;
				}
				if( sql_ch_name.numRowsAffected() == 0 )
				{
					sql_ch_name.finish();
					sql_sl_name.bindValue(0,_data[row]->barcode());
					if( !sql_sl_name.exec() )
					{
						database_error( sql_ch_name.lastError() );
						return false;
					}
					if( !sql_sl_name.next() )
					{
						sql_sl_name.finish();
						return row_dissapeared(row);
					}
					_data[row]->set_name(sql_sl_name.value(0).toString());
					_data[row]->name_changed = true;
					emit dataChanged( index, index );
					return true;
				}
				_data[row]->set_name(newname);
				_data[row]->name_changed = false;
				emit dataChanged( index, index );
				return true;
			}

		case pmcolprice:
			{
				auto oldprice = _data[row]->price();
				auto newpreprice = product::preprocess_price(value.toString());
				if( !product::check_price(newpreprice) )
					return false;
				auto newprice = product::parse_price(newpreprice);
				if( oldprice == newprice )
					return true;
				if( role == PretendSetRole )
					return true;

				sql_ch_price.bindValue(0,newprice);
				sql_ch_price.bindValue(1,_data[row]->barcode());
				sql_ch_price.bindValue(2,oldprice);
				if( !sql_ch_price.exec() )
				{
					database_error( sql_ch_price.lastError() );
					return false;
				}
				if( sql_ch_price.numRowsAffected() == 0 )
				{
					sql_ch_price.finish();
					sql_sl_price.bindValue(0,_data[row]->barcode());
					if( !sql_sl_price.exec() )
					{
						database_error( sql_ch_price.lastError() );
						return false;
					}
					if( !sql_sl_price.next() )
					{
						sql_sl_price.finish();
						return row_dissapeared(row);
					}
					_data[row]->set_price(sql_sl_price.value(0).toDouble());
					_data[row]->price_changed = true;
					emit dataChanged( index, index );
					return true;
				}
				_data[row]->set_price(newprice);
				_data[row]->price_changed = false;
				emit dataChanged( index, index );
				return true;
			}

		case pmcolstock:
			{
				auto oldstock = _data[row]->stock();
				auto newprestock = product::preprocess_stock(value.toString());
				if( !product::check_stock(newprestock) )
					return false;
				auto newstock = product::parse_stock(newprestock);
				if( oldstock == newstock )
					return true;
				if( role == PretendSetRole )
					return true;

				sql_ch_stock.bindValue(0,newstock);
				sql_ch_stock.bindValue(1,_data[row]->barcode());
				sql_ch_stock.bindValue(2,oldstock);
				if( !sql_ch_stock.exec() )
				{
					database_error( sql_ch_stock.lastError() );
					return false;
				}
				if( sql_ch_stock.numRowsAffected() == 0 )
				{
					sql_ch_stock.finish();
					sql_sl_stock.bindValue(0,_data[row]->barcode());
					if( !sql_sl_stock.exec() )
					{
						database_error( sql_ch_stock.lastError() );
						return false;
					}
					if( !sql_sl_stock.next() )
					{
						sql_sl_stock.finish();
						return row_dissapeared(row);
					}
					_data[row]->set_stock(sql_sl_stock.value(0).toUInt());
					_data[row]->stock_changed = true;
					emit dataChanged( index, index );
					return true;
				}
				_data[row]->set_stock(newstock);
				_data[row]->stock_changed = false;
				emit dataChanged( index, index );
				return true;
			}

			return false;
		}
	}

	return false;
}

Qt::ItemFlags
product_model::
flags( const QModelIndex & index ) const
{
	if( index.parent().isValid() )
		return Qt::NoItemFlags;

	unsigned row = index.row();
	if( row >= _data.size() )
		return Qt::NoItemFlags;

	Qt::ItemFlags read = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
	Qt::ItemFlags write = read | Qt::ItemIsEditable;
	int column = index.column();
	switch(column)
	{
	case pmcolcode: return write;
	case pmcolname: return write;
	case pmcolprice: return write;
	case pmcolstock: return write;
	default: return Qt::NoItemFlags;
	}

}

QVariant
product_model::
headerData( int column, Qt::Orientation orientation, int role ) const
{
	if( orientation == Qt::Horizontal )
		switch(role)
		{
		case Qt::DisplayRole:
		case Qt::EditRole:
			switch(column)
			{
			case pmcolcode: return tr("barcode");
			case pmcolname: return tr("name");
			case pmcolprice: return tr("price");
			case pmcolstock: return tr("stock");
			}
		}

	return QVariant();
}

void
product_model::
sort( int column, Qt::SortOrder order )
{
	qDebug() << "Sort:" << column << order;
}

enum ranged_prop
{	rpinvalid = -1
,  rpzero = 0
,	rpstock = 0
,	rpprice 
,	rpsize
};

constexpr ranged_prop inc_ranged_prop(ranged_prop rp)
{
	return static_cast<ranged_prop>(static_cast<unsigned>(rp)+1);
}

QString ranged_prop_string(ranged_prop rp)
{
	switch(rp)
	{
	case rpstock: return QStringLiteral("stock");
	case rpprice: return QStringLiteral("price");
	default: return QString();
	}
}

bool
product_model::
setSearchString( QString const & str )
{
	QString nstr = str.normalized(QString::NormalizationForm_C);
	int index = 0;
	int end = nstr.length();

	bool min_rppresent[rpsize];
	bool max_rppresent[rpsize];
	double min_rps[rpsize];
	double max_rps[rpsize];

	for( ranged_prop rpi = rpzero; rpi < rpsize; rpi = inc_ranged_prop(rpi) )
	{
		min_rppresent[rpi] = false;
		max_rppresent[rpi] = false;
	}

	std::vector<QString> wordSearch;

	auto set_min = [&]( ranged_prop rp, double x ) -> void
	{
		if( min_rppresent[rp] )
			min_rps[rp] = std::max(min_rps[rp], x);
		else
			min_rps[rp] = x;
		min_rppresent[rp] = true;
	};

	auto set_max = [&]( ranged_prop rp, double x ) -> void
	{
		if( max_rppresent[rp] )
			max_rps[rp] = std::min(max_rps[rp], x);
		else
			max_rps[rp] = x;
		max_rppresent[rp] = true;
	};

	auto skip_ws = [&]() -> bool
	{
		bool ws = false;
		while( index < end )
			if( nstr[index].isSpace() )
			{
				index += 1;
				ws = true;
			}
			else break;
		return ws;
	};

	auto parse_word = [&]() -> QString
	{
		int begin = index;
		while( index < end )
			if( !nstr[index].isSpace() )
				index += 1;
			else break;
		
		return nstr.mid(begin,index-begin);
	};

	auto parse_number = [&]() -> double
	{
		double accum = 0;
		while( index < end )
			if( static_cast<unsigned>(nstr.at(index).digitValue()) < 10 )
				accum = 10*accum + nstr.at(index++).digitValue();
			else break;
		if( nstr[index] != '.' ) return accum;

		index += 1;
		double mult = 0.1;
		while( index < end )
			if( static_cast<unsigned>(nstr.at(index).digitValue()) < 10 )
			{
				accum += mult*(nstr.at(index++).digitValue());
				mult *= 0.1;
			}
			else break;
		return accum;
	};

	auto parse_ranged_prop = [&]() -> ranged_prop
	{
		for( ranged_prop rp = rpzero; rp < rpsize; rp = inc_ranged_prop(rp))
		{
			QString rpstr = ranged_prop_string(rp);
			if( nstr.midRef(index).startsWith( rpstr, Qt::CaseInsensitive ) )
			{
				bool ok = true;
				if( index+rpstr.length() < end )
					if( nstr[index+rpstr.length()].isLetter() )
						ok = false;

				if(ok)
				{
					index += rpstr.length();
					return rp;
				}
			}
		}

		return rpinvalid;
	};

	auto parse_op = [&]( QString str ) -> bool
	{
		if( nstr.midRef(index).startsWith( str, Qt::CaseInsensitive ) )
		{
			bool ok = true;
			if( index+str.length() < end )
			{
				auto c = nstr.at(index+str.length());
				if( c.isPunct() || c.isSymbol() )
					ok = false;
			}

			if(ok)
			{
				index += str.length();
				return true;
			}
		}

		return false;
	};

	while( index < end )
	{
		ranged_prop rp;

		skip_ws();
		if( static_cast<unsigned>(nstr.at(index).digitValue()) < 10 )
		{
			double low = parse_number();
			skip_ws();
			if( parse_op("<") )
			{
				skip_ws();
				rp = parse_ranged_prop();
				if( rp == rpinvalid ) return false;
				set_min( rp, low );
				skip_ws();
				if( parse_op("<") )
				{
					skip_ws();
					double high = parse_number();

					set_max( rp, high );
				}
			}
			else return false;

			continue;
		}

		if((rp = parse_ranged_prop()) != rpinvalid)
		{
			skip_ws();

			if( parse_op("<") )
			{
				skip_ws();
				double high = parse_number();

				set_max( rp, high );
			}
			else wordSearch.push_back(ranged_prop_string(rp));

			continue;
		}

		// otherwise
		{
			QString word = parse_word();
			if( word.length() != 0 )
				wordSearch.push_back(word);
		}
	}

	QString sql = "SELECT code, name, price, stock FROM products";
	QString sep = " WHERE";
	QString sep_and = " AND";
	std::vector<QVariant> params;

	if( min_rppresent[rpprice] )
	{
		qDebug() << "min price: " << min_rps[rpprice];
		sql += sep;
		sql += " price > ?";
		sep = sep_and;
		params.push_back(min_rps[rpprice]);
	}
	if( max_rppresent[rpprice] )
	{
		qDebug() << "max price: " << max_rps[rpprice];
		sql += sep;
		sql += " price < ?";
		sep = sep_and;
		params.push_back(max_rps[rpprice]);
	}
	if( min_rppresent[rpstock] )
	{
		qDebug() << "min stock: " << min_rps[rpstock];
		sql += sep;
		sql += " stock > ?";
		sep = sep_and;
		params.push_back(min_rps[rpstock]);
	}
	if( max_rppresent[rpstock] )
	{
		qDebug() << "max stock: " << max_rps[rpstock];
		sql += sep;
		sql += " stock < ?";
		sep = sep_and;
		params.push_back(max_rps[rpstock]);
	}
	for( QString const str : wordSearch )
	{
		qDebug() << "word: " << str;
		sql += sep;
		sql += " name LIKE ?";
		sep = sep_and;
		params.push_back("%" + str + "%");
	}
	sql += ";";
	qDebug() << "SQL:" << sql;

	query.prepare(sql);
	index = 0;
	for( QVariant const & par : params )
		query.bindValue(index++,par);

	return true;
}

void
product_model::
refresh()
{
	query.exec();
	if( query.lastError().isValid() )
	{
		qCritical( "Database error!" );
		return;
	}

	beginResetModel();
	for( auto prod : _data )
		delete prod;
	_data.clear();
	while( query.next() )
		_data.push_back( new product_item( query.value(0).toString(), query.value(1).toString(), query.value(2).toDouble(), query.value(3).toUInt() ) );

	query.finish();
	endResetModel();
}

bool
product_model::
removeRows( int row, int count, QModelIndex const & parent )
{
	if( parent.isValid() )
		return false;

	if( count == 0 )
		return true;

	if( row + count >= _data.size() )
	{
		qCritical( "product_model: Tried to remove non existent row!" );
		return false;
	}

	QString sql = "DELETE FROM products";
	QString sep = " WHERE";
	for( auto prod = _data.begin()+row; prod < _data.begin()+row+count; prod += 1 )
	{
		sql += sep + " code = ?";
		sep = " AND";
	}
	QSqlQuery del( sql );
	for( auto prod = _data.begin()+row; prod < _data.begin()+row+count; prod += 1 )
		del.addBindValue( (*prod)->barcode() );
	if( del.exec() )
	{
		beginRemoveRows(QModelIndex(),row,row+count-1);
		_data.erase( _data.begin()+row, _data.begin()+row+count );
		endRemoveRows();
	}
	else
	{
		database_error( del.lastError() );
		return false;
	}
	return true;
}

