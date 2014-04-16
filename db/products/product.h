#ifndef PRODUCT_H
#define PRODUCT_H

#include <qstring.h>

class product
{
public:
    product();
    //product(QString arg1,QString arg2, double arg3, int arg4)
    ~product(){}
	bool check_barcode();
	static bool check_barcode(QString code);

private:
    QString code;
    QString name;
    double price;
    int stock;
};

#endif // PRODUCT_H
