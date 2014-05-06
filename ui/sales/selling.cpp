#include "selling.h"
#include "ui_selling.h"
#include <QAction>
Selling::Selling(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Selling)
{
    ui->setupUi(this);
    set_user_text("Pekka Liukko");//----------------------------------------------------------------
    set_image_buttons();
    thanks_timer = new QTimer();
    thanks_timer->setInterval(5000);
    QObject::connect(thanks_timer, SIGNAL(timeout()), this, SLOT(clear_thanks_text()));
}

void Selling::clear_thanks_text()
{
    ui->l_thanks->setText("");
    thanks_timer->stop();
}

void Selling::set_image_buttons()
{
    QPixmap kokis = QPixmap(":images/kokis.jpg");
    ui->b_coke->setIcon(QIcon(kokis));
    ui->b_coke->setIconSize(QSize(kokis.rect().size()));

    QPixmap pepsi = QPixmap(":images/pepsi.jpg");
    ui->b_pepsi->setIcon(QIcon(pepsi));
    ui->b_pepsi->setIconSize(QSize(pepsi.rect().size()));

    QPixmap daniels = QPixmap(":images/daniels.jpg");
    ui->b_daniels->setIcon(QIcon(daniels));
    ui->b_daniels->setIconSize(daniels.rect().size());

    QPixmap twix = QPixmap(":images/twix.jpg");
    ui->b_twix->setIcon(QIcon(twix));
    ui->b_twix->setIconSize(twix.rect().size());

    QPixmap banaani = QPixmap(":images/banaani.jpg");
    ui->b_banaani->setIcon(QIcon(banaani));
    ui->b_banaani->setIconSize(banaani.rect().size());
}

void Selling::modified(int a, int b)
{
    qDebug() << a << b;
    cell.prepare("SELECT * from products");
    cell.exec();
}

Selling::~Selling()
{
    delete ui;
}

void Selling::set_arrow(QLabel& labelname)
{
    ui->l_banaani->hide();
    ui->l_coke->hide();
    ui->l_pepsi->hide();
    ui->l_daniels->hide();
    ui->l_twix->hide();
    QPixmap arrow = QPixmap(":images/leftarrow.png");
    labelname.setPixmap(arrow);
    labelname.show();
}
void Selling::details(QString nimi)
{
    current_product = nimi;
    products.prepare("SELECT name, price, description,code FROM products Where name = ?;");
    products.bindValue(0,nimi);
    products.exec();
    while(products.next())
    {
        ui->label_name->setText(products.value(0).toString());
        ui->label_price->setText(products.value(1).toString()+" €");
        ui->label_description->setText(products.value(2).toString());
        ui->l_code->setText(products.value(3).toString());
    }
    products.finish();
}
void Selling::on_b_coke_clicked()   {set_arrow(*ui->l_coke);details("Coka Cola");}
void Selling::on_b_pepsi_clicked()  {set_arrow(*ui->l_pepsi);details("Pepsi");}
void Selling::on_b_daniels_clicked(){set_arrow(*ui->l_daniels);details("Jack Daniels");}
void Selling::on_b_twix_clicked()   {set_arrow(*ui->l_twix);details("Twix");}
void Selling::on_b_banaani_clicked(){set_arrow(*ui->l_banaani);details("Banaani");}


void Selling::set_user_text(QString nimi)
{
    products.prepare("SELECT user_money FROM users Where name = ?;");
    products.bindValue(0,nimi);
    products.exec();
    while(products.next())
    {
        ui->label_user_name->setText(nimi);
        ui->label_money->setText(products.value(0).toString()+" €");
    }
    products.finish();

}


void Selling::on_pushButton_osta_clicked()
{
    QString card_number = "9633ADB54C"; //----------------------------------------------------------------
    QString nimi = "Pekka Liukko";//----------------------------------------------------------------
    QSqlQuery query;

    query.prepare("UPDATE users SET user_money = user_money-? Where name = ?;");
    query.bindValue(0,ui->label_price->text());
    query.bindValue(1,nimi);
    query.exec();
    query.finish();

    QSqlQuery querys;
    querys.prepare("INSERT INTO sales_event VALUES(Null,?,?,NOW()); SELECT LAST_INSERT_ID();");
    querys.bindValue(0,card_number);
    querys.bindValue(1,ui->label_price->text());//QString::number(.toInt(),'f',2));//total price
    querys.exec();
    int sale_event_id;
    if(querys.nextResult() ){
        if( querys.next())
            sale_event_id = querys.value(0).toInt();
    }
    querys.finish();

    QSqlQuery que;
    qDebug() << sale_event_id;
    que.prepare("INSERT INTO sales_row VALUES(Null,?,?,?);UPDATE products SET stock=stock-? WHERE code = ?");
    que.bindValue(0,sale_event_id);
    que.bindValue(1,ui->l_code->text());
    que.bindValue(2,1);
    que.bindValue(3,1);
    que.bindValue(4,ui->l_code->text());
    que.exec();
    que.finish();
    set_user_text(nimi);

    ui->l_thanks->setText("Kiitos ostoksesta, Nautinnollisia hetkiä!!");
    thanks_timer->start();
}
