
#include <db/utilities.h>
#include <QMessageBox>

void critical_error( QString const msg )
{
	QMessageBox msgb;

	msgb.setText(msg);
	msgb.setIcon(QMessageBox::Critical);
	msgb.exec();
}

void database_error( QSqlError const & err )
{
	QMessageBox msgb;

	msgb.setText("Database error: " + err.text());
	msgb.setIcon(QMessageBox::Critical);
	msgb.exec();
}

