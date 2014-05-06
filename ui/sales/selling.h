#ifndef SELLING_H
#define SELLING_H

#include <QDialog>
#include <QtSql>
#include <QLabel>
#include <db/users/user.h>

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
    void set_image_buttons();
    void set_arrow(QLabel &labelname);
    void details(QString);
    void set_user_text(user u);
    QString current_product;
    int row_Amount;
    QSqlQuery products;
    QSqlQuery cell;
    QTimer* thanks_timer;

private slots:
	 void on_login(user u);
    void on_b_coke_clicked();
    void on_b_pepsi_clicked();
    void on_b_daniels_clicked();
    void on_b_twix_clicked();
    void on_b_banaani_clicked();
    void on_pushButton_osta_clicked();
    void clear_thanks_text();
};

#endif // SELLING_H
