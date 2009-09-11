#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtCore/QTimer>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	// created in stack - no leak
	QWidget widget1;
	widget1.show();
	widget1.activateWindow();
	widget1.setFocus();

	// created with parent
	QWidget *widget2 = new QWidget(&widget1);
	widget2->setObjectName(widget1.objectName() + "_2");

	// create and destroy
	QWidget *widget3 = new QWidget;
	widget3->show();
	delete widget3;

	// delete later
	QWidget *widget4 = new QWidget;
	widget4->show();
	widget4->activateWindow();
	widget4->setFocus();
	widget4->deleteLater();

	QTimer::singleShot(500, &widget1, SLOT(close()));
	return app.exec();
}
