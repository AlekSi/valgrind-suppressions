#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtCore/QTimer>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	// created in stack - no leak
	QWidget widget1;

	// created with parent
	QWidget *widget2 = new QWidget(&widget1);
	widget2->setObjectName(widget1.objectName() + "_2");

	// create and destroy
	QWidget *widget3 = new QWidget;
	delete widget3;

	QTimer::singleShot(500, qApp, SLOT(quit()));
	return app.exec();
}
