#ifndef TUOTEHALLINTA_H
#define TUOTEHALLINTA_H

#include <QDialog>
#include <set>
#include <QtSql/QSqlTableModel>

namespace Ui {
class product;
}

class product : public QDialog
{
    Q_OBJECT

public:
    explicit product(QWidget *parent = 0);
    ~product();

private:
   // QSqlTableModel* product;
    Ui::product *ui;
    QString code;
    QString name;
    double price;
    //std::set<QString> tuoteryhma;-+

    int stock;
};

#endif // TUOTEHALLINTA_H
