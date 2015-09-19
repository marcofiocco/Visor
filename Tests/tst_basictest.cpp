#include <QString>
#include <QtTest>

class BasicTest : public QObject
{
    Q_OBJECT

public:
    BasicTest();

private Q_SLOTS:
    void testCase1();
};

BasicTest::BasicTest()
{
}

void BasicTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(BasicTest)

#include "tst_basictest.moc"
