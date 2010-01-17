#include <QtCore/QCoreApplication>
#include <QtCore/QSharedPointer>
#include <QtCore/QScopedPointer>
#include <QtCore/QTimer>

static void doDeleteLater(QObject *obj)
{
	obj->deleteLater();
}

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	// created in stack - no leak
	QObject obj1;

	// created with parent
	QObject *obj2 = new QObject(qApp);
	obj2->setObjectName(obj1.objectName() + "_2");

	// create and destroy
	QObject *obj3 = new QObject;
	delete obj3;

	QSharedPointer<QObject> obj4(new QObject);
	QSharedPointer<QObject> obj5(new QObject, doDeleteLater);
	QScopedPointer<QObject> obj6(new QObject);

	QTimer::singleShot(500, qApp, SLOT(quit()));
	return app.exec();
}
