#include "product.h"

#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QDebug>

bool product::check_barcode()
{
	return product::check_barcode(_code);
}

bool product::check_barcode(QString barcode)
{
	char a[13];
    QByteArray code_array;
    code_array = barcode.toLatin1();
    strncpy(a,code_array.data(),13);
    QString HexNum, checking;
    char temp[13];
    int check_digit;
    for(int i=0;i<=12;i++)
    {
        sprintf(temp,"%x",a[i]);
        HexNum = temp;
        checking = checking + HexNum.right(1);
    }
    int sum_odd=(a[0] - '0')+(a[2] -'0')+(a[4]-'0')+(a[6]-'0')+(a[8]-'0')+(a[10]-'0');
    int sum_even=(a[1]-'0')+(a[3]-'0')+(a[5]-'0')+(a[7]-'0')+(a[9]-'0');
    sum_odd = sum_odd * 3;
    int sum = sum_odd + sum_even;
    int last_digit = sum%10;
    check_digit = 10-last_digit;
    if(check_digit == (a[11]-'0'))
    {
        return true;
    }else
    {
        return false;
    }
}

void product::set_data(QString nimi)
{
    QSqlQuery query;
    query.exec("select * from products where name='"+nimi+"'");
    while (query.next()){
        this->code = query.value(0).toString();
        this->name = query.value(1).toString();
        this->price = query.value(2).toDouble();
        this->stock = query.value(3).toInt();
    }
}
