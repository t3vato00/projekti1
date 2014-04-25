#ifndef MYYNTI_H
#define MYYNTI_H

#include <QDialog>
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

    void on_pushButton_lisaa_tuote_clicked();

    void on_lineEdit_m_maara_textChanged(const QString &maara);

    void on_lineEdit_m_nimi_textChanged(const QString &arg1);

    void on_lineEdit_m_nimi_editingFinished();

    void on_lineEdit_clear_clicked();

    void on_myy_clicked();

private:
    Ui::sale *ui;
    QStringList product_wordlist;
    int row_number;
    int stock_amount;
    double total_price;
    double product_price;
    QString current_product_name;
    product* new_product;
    QVector<sales_row> sales_list;
    void delete_row(int);

    void clear_lineEdits();
    void set_wordlist();
    void add_row_to_list();

};

#endif // MYYNTI_H
