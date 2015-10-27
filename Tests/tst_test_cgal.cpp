#include <QString>
#include <QtTest>

#include <Core/FindGeometryVisitor.h>
#include <osgDB/ReadFile>

#include <CGAL/Simple_cartesian.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_triangle_primitive.h>

typedef CGAL::Simple_cartesian<double> K;
typedef K::FT FT;
typedef K::Ray_3 Ray;
typedef K::Line_3 Line;
typedef K::Point_3 Point;
typedef K::Triangle_3 Triangle;
typedef std::list<Triangle>::iterator Iterator;
typedef CGAL::AABB_triangle_primitive<K, Iterator> Primitive;
typedef CGAL::AABB_traits<K, Primitive> AABB_triangle_traits;
typedef CGAL::AABB_tree<AABB_triangle_traits> Tree;

class CGALTest : public QObject
{
    Q_OBJECT

public:
    CGALTest();

private Q_SLOTS:
    void testCase1();
};

CGALTest::CGALTest()
{
}

void CGALTest::testCase1()
{
    osg::Node* model = osgDB::readNodeFile("cow.osg");

    QVERIFY(model);

    if (model)
    {
        Visor::FindGeometryVisitor fgv;
        model->accept(fgv);

        std::list<Triangle> triangles;
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

                        Point p0(v0.x(), v0.y(), v0.z());
                        Point p1(v1.x(), v1.y(), v1.z());
                        Point p2(v2.x(), v2.y(), v2.z());

                        triangles.push_back(Triangle(p0, p1, p2));
                    }
                    break;
                case osg::PrimitiveSet::TRIANGLE_STRIP: // type 5
                    for (int t = 2; t < primitive.getIndices().size(); ++t) {
                        const Visor::Vertex& v0 = geometry.vertexArray()[primitive.getIndices()[t - 2]];
                        const Visor::Vertex& v1 = geometry.vertexArray()[primitive.getIndices()[t - 1]];
                        const Visor::Vertex& v2 = geometry.vertexArray()[primitive.getIndices()[t]];

                        Point p0(v0.x(), v0.y(), v0.z());
                        Point p1(v1.x(), v1.y(), v1.z());
                        Point p2(v2.x(), v2.y(), v2.z());

                        triangles.push_back(Triangle(p0, p1, p2));
                    }
                    break;
                case osg::PrimitiveSet::TRIANGLE_FAN: // type 6
                    for (int t = 2; t < primitive.getIndices().size(); ++t) {
                        const Visor::Vertex& v0 = geometry.vertexArray()[primitive.getIndices()[0]];
                        const Visor::Vertex& v1 = geometry.vertexArray()[primitive.getIndices()[t - 1]];
                        const Visor::Vertex& v2 = geometry.vertexArray()[primitive.getIndices()[t]];

                        Point p0(v0.x(), v0.y(), v0.z());
                        Point p1(v1.x(), v1.y(), v1.z());
                        Point p2(v2.x(), v2.y(), v2.z());

                        triangles.push_back(Triangle(p0, p1, p2));
                    }
                    break;
                default:
                    QFAIL("Primitive type not supported!");
                }
            }
        }
        // constructs AABB tree
        Tree tree(triangles.begin(),triangles.end());
        // counts #intersections
        Point a(1.0, 0.0, 0.0); // ### FIXME ###: make sure the ray intersects the model, are these coordinates right?
        Point b(0.0, 1.0, 0.0);
        Ray ray_query(a, b);
        std::cout << tree.number_of_intersected_primitives(ray_query) << " intersections(s) with ray query" << std::endl;
        // compute closest point and squared distance
        Point point_query(2.0, 2.0, 2.0);
        Point closest_point = tree.closest_point(point_query);
        std::cerr << "closest point is: " << closest_point << std::endl;
        FT sqd = tree.squared_distance(point_query);
        std::cout << "squared distance: " << sqd << std::endl;
    }
}

QTEST_APPLESS_MAIN(CGALTest)

#include "tst_test_cgal.moc"
