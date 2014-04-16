#ifndef PRODUCT_H
#define PRODUCT_H

#include <qstring.h>

class product
{
	QString _code;
	QString _name;
	double _price;
	unsigned _stock;

public:

	inline product()
	: _code(""), _name(""), _price(0), _stock(0)
	{
	}

	inline product(QString code, QString name, double price, int stock)
	: _code(code), _name(name), _price(price), _stock(stock)
	{
	}

	bool check_barcode();
	static bool check_barcode(QString code);

	inline QString barcode() const { return _code; }
	inline QString name() const { return _name; }
	inline double price() const { return _price; }
	inline int stock() const { return _stock; }

	inline void setBarcode( QString x ) { _code = x; }
	inline void setName( QString x ) { _name = x; }
	inline void setPrice( double x ) { _price = x; }
	inline void setStock( unsigned x ) { _stock = x; }

};

#endif // PRODUCT_H
