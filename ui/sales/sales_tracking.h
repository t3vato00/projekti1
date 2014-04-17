#ifndef SALES_TRACKING_H
#define SALES_TRACKING_H

#include <QDialog>

namespace Ui {
class sales_tracking;
}

class sales_tracking : public QDialog
{
    Q_OBJECT

public:
    explicit sales_tracking(QWidget *parent = 0);
    ~sales_tracking();

private:
    Ui::sales_tracking *ui;
};

#endif // SALES_TRACKING_H
