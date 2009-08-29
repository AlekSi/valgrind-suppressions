#include <QtCore/QCoreApplication>
#include <QtCore/QTimer>

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

	QTimer::singleShot(500, qApp, SLOT(quit()));
	return app.exec();
}
