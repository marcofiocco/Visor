#include <QString>
#include <QtTest>

#include <Core/FindGeometryVisitor.h>
#include <osgDB/ReadFile>

#include <openvdb/openvdb.h>

class OpenVDBTest : public QObject
{
    Q_OBJECT

public:
    OpenVDBTest();

private Q_SLOTS:
    void testCase1();
};

OpenVDBTest::OpenVDBTest()
{
}

void OpenVDBTest::testCase1()
{
    osg::Node* model = osgDB::readNodeFile("cow.osg");

    QVERIFY(model);

    if (model)
    {
        Visor::FindGeometryVisitor fgv;
        model->accept(fgv);

        for (int g = 0; g < fgv.geometryArray().size(); ++g)
        {
            const Visor::Geometry& geometry = fgv.geometryArray()[g];
            for (int p = 0; p < geometry.primitiveArray().size(); ++p)
            {
                const Visor::Primitive& primitive = geometry.primitiveArray()[p];
                switch (primitive.getType())
                {
                case osg::PrimitiveSet::TRIANGLES: // type 4
                    for (int i = 0; i < primitive.getIndices().size(); i += 3) {
                        const Visor::Vertex& v0 = geometry.vertexArray()[primitive.getIndices()[i]];
                        const Visor::Vertex& v1 = geometry.vertexArray()[primitive.getIndices()[i + 1]];
                        const Visor::Vertex& v2 = geometry.vertexArray()[primitive.getIndices()[i + 2]];

                        // Put Vertex data in your data structure!
                    }
                    break;
                case osg::PrimitiveSet::TRIANGLE_STRIP: // type 5
                    for (int t = 2; t < primitive.getIndices().size(); ++t) {
                        const Visor::Vertex& v0 = geometry.vertexArray()[primitive.getIndices()[t - 2]];
                        const Visor::Vertex& v1 = geometry.vertexArray()[primitive.getIndices()[t - 1]];
                        const Visor::Vertex& v2 = geometry.vertexArray()[primitive.getIndices()[t]];

                        // Put Vertex data in your data structure!
                    }
                    break;
                case osg::PrimitiveSet::TRIANGLE_FAN: // type 6
                    for (int t = 2; t < primitive.getIndices().size(); ++t) {
                        const Visor::Vertex& v0 = geometry.vertexArray()[primitive.getIndices()[0]];
                        const Visor::Vertex& v1 = geometry.vertexArray()[primitive.getIndices()[t - 1]];
                        const Visor::Vertex& v2 = geometry.vertexArray()[primitive.getIndices()[t]];

                        // Put Vertex data in your data structure!
                    }
                    break;
                default:
                    QFAIL("Primitive type not supported!");
                }
            }
        }

        // Set up OpenVDB here

        // Initialize the OpenVDB library.  This must be called at least
        // once per program and may safely be called multiple times.
        openvdb::initialize();
        // Create an empty floating-point grid with background value 0.
        openvdb::FloatGrid::Ptr grid = openvdb::FloatGrid::create();
        std::cout << "Testing random access:" << std::endl;
        // Get an accessor for coordinate-based access to voxels.
        openvdb::FloatGrid::Accessor accessor = grid->getAccessor();
        // Define a coordinate with large signed indices.
        openvdb::Coord xyz(1000, -200000000, 30000000);

        // Set the voxel value at (1000, -200000000, 30000000) to 1.
        accessor.setValue(xyz, 1.0);

        // Verify that the voxel value at (1000, -200000000, 30000000) is 1.
        std::cout << "Grid" << xyz << " = " << accessor.getValue(xyz) << std::endl;

        // Reset the coordinates to those of a different voxel.
        xyz.reset(1000, 200000000, -30000000);

        // Verify that the voxel value at (1000, 200000000, -30000000) is
        // the background value, 0.
        std::cout << "Grid" << xyz << " = " << accessor.getValue(xyz) << std::endl;

        // Set the voxel value at (1000, 200000000, -30000000) to 2.
        accessor.setValue(xyz, 2.0);
        // Set the voxels at the two extremes of the available coordinate space.
        // For 32-bit signed coordinates these are (-2147483648, -2147483648, -2147483648)
        // and (2147483647, 2147483647, 2147483647).
        accessor.setValue(openvdb::Coord::min(), 3.0f);
        accessor.setValue(openvdb::Coord::max(), 4.0f);
        std::cout << "Testing sequential access:" << std::endl;
        // Print all active ("on") voxels by means of an iterator.
        for (openvdb::FloatGrid::ValueOnCIter iter = grid->cbeginValueOn(); iter; ++iter) {
            std::cout << "Grid" << iter.getCoord() << " = " << *iter << std::endl;
        }
    }
}

QTEST_APPLESS_MAIN(OpenVDBTest)

#include "tst_test_openvdb.moc"
