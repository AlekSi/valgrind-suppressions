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
		QSqlQuery q1("CREATE TABLE t (i INTEGER)", db);
		q1.prepare("INSERT INTO t (i) VALUES(?)");
		q1.addBindValue(42);
		q1.exec();
		db.commit();

		db.transaction();
		QSqlQuery q2(db);
		q2.setForwardOnly(true);
		q2.setForwardOnly(false);
		q2.exec("SELECT * FROM t");
		q2.first();
		int value = q2.value(0).toInt();
		Q_ASSERT(value == 42);
		q2.last();
		q2.finish();
	}
	QSqlDatabase::removeDatabase("connection_name");

	QTimer::singleShot(500, qApp, SLOT(quit()));
	return app.exec();
}
