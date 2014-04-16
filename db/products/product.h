#ifndef PRODUCT_H
#define PRODUCT_H

#include <qstring.h>

class product
{
public:
    product();
    //product(QString arg1,QString arg2, double arg3, int arg4)
    ~product(){}

private:
    QString code;
    QString name;
    double price;
    int stock;
};

#endif // PRODUCT_H
