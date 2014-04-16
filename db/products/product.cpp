#include "product.h"

#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QDebug>

product::product()
{
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
