#ifndef HEADER_DB_UTILITIES
#define HEADER_DB_UTILITIES

#include <QString>
#include <QSqlError>

const int PretendSetRole = Qt::UserRole;

inline
QString
normalize_string_input( QString const & q )
{
	return q.normalized(QString::NormalizationForm_C).trimmed();
}

void critical_error( QString const msg );

void database_error( QSqlError const & err );

#endif // HEADER_DB_UTILITIES
