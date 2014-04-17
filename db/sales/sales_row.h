#ifndef SALES_ROW_H
#define SALES_ROW_H
#include <QString>

class sales_row
{
public:
    sales_row();
    sales_row(int,QString, double);
    ~sales_row();
    QString product_code;
    double amount;
    int sales_id;
};

#endif // SALES_ROW_H
