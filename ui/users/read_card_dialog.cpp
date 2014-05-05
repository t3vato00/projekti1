#include "read_card_dialog.h"
#include "ui_read_card_dialog.h"

read_card_dialog::read_card_dialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::read_card_dialog)
{
    ui->setupUi(this);
	 QObject::connect(&login::singleton(), &login::show_card_dialog, this, &read_card_dialog::show_card_dialog );
}

void
read_card_dialog::show_card_dialog( login::read_rfid_status stat )
{
	if( stat == login::new_card )
		ui->label->setText( "place the new card onto the reader." );
	else if( stat == login::old_card )
		ui->label->setText( "place the old card onto the reader." );
}

read_card_dialog::~read_card_dialog()
{
    delete ui;
}
