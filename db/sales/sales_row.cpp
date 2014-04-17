#include "sales_row.h"

sales_row::sales_row()
{
}
sales_row::~sales_row(){}
sales_row::sales_row(int saleid, QString code, double amount)
{
    this->product_code = code;
    this->amount = amount;
    this->sales_id = saleid;
}
