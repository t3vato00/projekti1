#include "product.h"
#include <db/utilities.h>

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
    if(barcode.length() != 12)
    {
        return false;
    }else
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

}

QString
product::
preprocess_name(QString const name)
{
	return normalize_string_input( name );
}

bool
product::
check_name(QString const name)
{
	if( name.length() == 0 )
		return false;

	return !name.at(0).isSpace() || !name.at(name.length()-1).isSpace();
}

QString
product::
parse_name(QString const name)
{
	return name;
}

QString
product::
preprocess_price(QString const price)
{
	return normalize_string_input( price );
}

bool
product::
check_price(QString const str)
{
	bool ok;
	double price = str.toDouble(&ok);

	return ok && price >= 0;
}

double
product::
parse_price(QString const price)
{
	return price.toDouble();
}

QString
product::
preprocess_stock(QString const stock)
{
	return normalize_string_input( stock );
}

bool
product::
check_stock(QString const str)
{
	bool ok;
	unsigned stock = str.toUInt(&ok);

	return ok;
}

unsigned
product::
parse_stock(QString const stock)
{
	return stock.toUInt();
}

void product::set_by_name(QString nimi)
{
    QSqlQuery query;

    query.prepare("select * from products where name=?");
    query.bindValue(0,nimi);
    query.exec();
    while (query.next()){
        this->_code = query.value(0).toString();
        this->_name = query.value(1).toString();
        this->_price = query.value(2).toDouble();
        this->_stock = query.value(3).toInt();
    }
}
