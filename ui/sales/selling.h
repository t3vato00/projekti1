#ifndef SELLING_H
#define SELLING_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class Selling;
}

class Selling : public QDialog
{
    Q_OBJECT

public:
    explicit Selling(QWidget *parent = 0);
    ~Selling();

private:
    Ui::Selling *ui;
    int row_Amount;
    QSqlQuery products;
    QSqlQuery cell;
    void load_products();
    void add_row_to_list(QString, QString);

private slots:
    void modified(int,int);
};

#endif // SELLING_H
