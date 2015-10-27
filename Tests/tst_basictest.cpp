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
    osg::Node* model = osgDB::readNodeFile("cow.osg");

    QVERIFY(model);

    if (model)
    {
        Visor::FindGeometryVisitor fgv;
        model->accept(fgv);

        std::cout << "Model geometry blocks: " << fgv.geometryArray().size() << std::endl;
        QVERIFY(fgv.geometryArray().size() == 1);
        for (int g = 0; g < fgv.geometryArray().size(); ++g)
        {
            const Visor::Geometry& geometry = fgv.geometryArray()[g];

            std::cout << "   Geometry vertex array size: " << geometry.vertexArray().size() << std::endl;
            QVERIFY(geometry.vertexArray().size() == 7772);

            std::cout << "   Geometry primitive arrays: " << geometry.primitiveArray().size() << std::endl;
            QVERIFY(geometry.primitiveArray().size() == 1);
            for (int p = 0; p < geometry.primitiveArray().size(); ++p)
            {
                const Visor::Primitive& primitive = geometry.primitiveArray()[p];
                std::cout << "       Primitive (type " << primitive.getType() << ") size: " << primitive.getIndices().size() << std::endl;
                QVERIFY(primitive.getIndices().size() == 7772);
            }
        }
    }
}

QTEST_APPLESS_MAIN(BasicTest)

#include "tst_basictest.moc"
