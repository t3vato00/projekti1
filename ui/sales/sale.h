#ifndef MYYNTI_H
#define MYYNTI_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QtSql/QSqlTableModel>
#include "db/products/product.h"
#include "db/sales/sales_row.h"
#include <QVector>

namespace Ui {
class sale;
}

class sale : public QDialog
{
    Q_OBJECT

public:
    explicit sale(QWidget *parent = 0);
    ~sale();

private slots:

    void on_b_add_clicked();

    void on_product_amount_textChanged(const QString &maara);

    void on_product_name_textChanged(const QString &arg1);

    void on_product_name_editingFinished();

    void on_b_clear_clicked();

    void on_b_sell_clicked();

    void on_new_event_clicked();

    void on_b_delete_row_clicked();

    void on_b_delete_all_clicked();

private:
    Ui::sale *ui;
    QSqlQueryModel *sales_row;
    QStringList product_wordlist;
    int row_number;
    int stock_amount;
    double total_price;
    double product_price;
    int sale_event_id;
    QString current_product_name;
    product* new_product;

    void refresh_total_sum();
    void delete_row(QString, QString, int);
    void disable_all();
    void enable_all();
    void refresh_list();
    void clear_lineEdits();
    void set_wordlist();

};

#endif // MYYNTI_H
