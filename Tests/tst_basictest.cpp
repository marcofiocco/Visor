#include <QString>
#include <QtTest>

#include <Core/FindGeometryVisitor.h>
#include <osgDB/ReadFile>

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
    osg::Node* model = osgDB::readNodeFile("glider.osg");

    QVERIFY(model);

    if (model)
    {
        FindGeometryVisitor fgv;
        model->accept(fgv);

        std::cout << "Model size: " << fgv.vertexArrays().size() << std::endl;
        QVERIFY(fgv.vertexArrays().size() == 6);
    }
}

QTEST_APPLESS_MAIN(BasicTest)

#include "tst_basictest.moc"
