#include <QString>
#include <QtTest>

#include <Core/GeometryImporter.h>

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
    GeometryImporter g;
    QCOMPARE(g.process(), true);
}

QTEST_APPLESS_MAIN(BasicTest)

#include "tst_basictest.moc"
