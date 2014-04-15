#ifndef MYYNTI_H
#define MYYNTI_H

#include <QDialog>
#include <QtSql/QSqlTableModel>

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

private:
    Ui::sale *ui;
    QSqlTableModel* product;
    int row_number;
    int ostokset_yhteensa;
    int tuote_hinta;
};

#endif // MYYNTI_H
