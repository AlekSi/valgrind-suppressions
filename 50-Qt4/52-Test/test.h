#include <QtTest>

class MyTest : public QObject
{
	Q_OBJECT

private slots:
	void initTestCase()
	{
		QVERIFY(true);
	}

	void cleanupTestCase()
	{
		QCOMPARE(2+2, 4);
	}

	void init()
	{
	}

	void cleanup()
	{
	}

	void test()
	{
		QCOMPARE(2.0 + 2.0, 4.0);
	}
};

QTEST_MAIN(MyTest)