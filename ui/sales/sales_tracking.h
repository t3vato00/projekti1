#ifndef SALES_TRACKING_H
#define SALES_TRACKING_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QTimer>
namespace Ui {
class sales_tracking;
}

class sales_tracking : public QDialog
{
    Q_OBJECT

public:
    explicit sales_tracking(QWidget *parent = 0);
    ~sales_tracking();

private slots:
    void on_pushButton_clicked();
    void update_view();
private:
    Ui::sales_tracking *ui;
    QTimer *refresh_timer;
    QSqlTableModel *model;
    QSqlQueryModel *row_model;
};

#endif // SALES_TRACKING_H
