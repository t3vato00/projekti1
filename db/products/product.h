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
    void set_by_name(QString);
	static bool check_barcode(QString code);

	static QString preprocess_name(QString const name);
	static bool check_name(QString const name);
	static QString parse_name(QString const name);

	static QString preprocess_price(QString const price);
	static bool check_price(QString const price);
	static double parse_price(QString const price);

	static QString preprocess_stock(QString const stock);
	static bool check_stock(QString const stock);
	static unsigned parse_stock(QString const stock);

	inline QString barcode() const { return _code; }
	inline QString name() const { return _name; }
	inline double price() const { return _price; }
	inline int stock() const { return _stock; }

	inline void set_barcode( QString x ) { _code = x; }
	inline void set_name( QString x ) { _name = x; }
	inline void set_price( double x ) { _price = x; }
	inline void set_stock( unsigned x ) { _stock = x; }
};

#endif // PRODUCT_H
