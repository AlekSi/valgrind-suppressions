#include <QtCore/QCoreApplication>
#include <QtCore/QTimer>
#include <QtSql>

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	QSqlDatabase db1();

	{
		QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "connection_name");
		db.setDatabaseName(":memory:");
		db.open();
		db.transaction();
		QSqlQuery q("CREATE TABLE t (i INTEGER)", db);
		q.prepare("INSERT INTO t (i) VALUES(?)");
		q.addBindValue(42);
		q.exec();
		db.commit();

		db.transaction();
		q.setForwardOnly(true);
		q.setForwardOnly(false);
		q.exec("SELECT * FROM t");
		q.first();
		int value = q.value(0).toInt();
		Q_ASSERT(value == 42);
		q.last();
		q.finish();
	}
	QSqlDatabase::removeDatabase("connection_name");

	QTimer::singleShot(500, qApp, SLOT(quit()));
	return app.exec();
}
