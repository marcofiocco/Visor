#include "FindGeometryVisitor.h"
#include <osg/Drawable>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/TriangleFunctor>
#include <osg/io_utils>
#include <iostream>

class AttributePrinter : public osg::Drawable::AttributeFunctor
{
public:
    typedef osg::Drawable::AttributeType AttributeType;
    inline const char* getTypeName( AttributeType type )
    {
        static const char* typeNames[] =
        {
            "Vertices", "Weights", "Normals", "Colors", "Secondary Colors",
            "Fog Coords", "Attribute 6", "Attribute 7",
            "Texture Coords 0", "Texture Coords 1", "Texture Coords 2",
            "Texture Coordinates 3", "Texture Coords 4", "Texture Coords 5",
            "Texture Coords 6", "Texture Coords 7"
        };
        return typeNames[type];
    }

    template<typename T>
    void printInfo( AttributeType type, unsigned int size, T* front )
    {
        std::cout << "*** " << getTypeName(type) << ": " << size << std::endl;
        for ( unsigned int i=0; i<size; ++i )
            std::cout << "(" << *(front+i) << "); ";
        std::cout << std::endl << std::endl;
    }

    virtual void apply( AttributeType type, unsigned int size, float* front )
    { printInfo( type, size, front ); }

    virtual void apply( AttributeType type, unsigned int size, osg::Vec2* front )
    { printInfo( type, size, front ); }

    virtual void apply( AttributeType type, unsigned int size, osg::Vec3* front )
    { printInfo( type, size, front ); }

    virtual void apply( AttributeType type, unsigned int size, osg::Vec4* front )
    { printInfo( type, size, front ); }
};

struct TrianglePrinter
{
    TrianglePrinter()
    { std::cout << "*** Triangles ***" << std::endl; }

    void operator()( const osg::Vec3& v1, const osg::Vec3& v2, const osg::Vec3& v3, bool ) const
    { std::cout << "(" << v1 << ");(" << v2 << ");(" << v3 << ")" << std::endl; }
};

FindGeometryVisitor::FindGeometryVisitor() : osg::NodeVisitor(TRAVERSE_ALL_CHILDREN)
{
    _vertexArrays.clear();
}

void FindGeometryVisitor::apply(osg::Node& node)
{
    traverse(node);
}

void FindGeometryVisitor::apply(osg::Geode& node)
{
    for (unsigned int i = 0; i < node.getNumDrawables(); ++i )
    {
        osg::Drawable* drawable = node.getDrawable(i);
        if (!drawable) continue;
        std::cout << "[" << drawable->libraryName() << "::" << drawable->className() << "]" << std::endl;

        osg::Geometry* geom = dynamic_cast<osg::Geometry*>(drawable);
        if (geom)
        {
            osg::Geometry::PrimitiveSetList& primitives = geom->getPrimitiveSetList();
            osg::Geometry::PrimitiveSetList::iterator itr;
            unsigned int numSurfacePrimitives = 0;
            for (itr = primitives.begin(); itr != primitives.end(); ++itr)
            {
                switch((*itr)->getMode())
                {
                    case(osg::PrimitiveSet::TRIANGLES):
                    case(osg::PrimitiveSet::TRIANGLE_STRIP):
                    case(osg::PrimitiveSet::TRIANGLE_FAN):
                    case(osg::PrimitiveSet::QUADS):
                    case(osg::PrimitiveSet::QUAD_STRIP):
                    case(osg::PrimitiveSet::POLYGON):
                        ++numSurfacePrimitives;
                        break;
                    default:
                        break;
                }
            }

            if (!numSurfacePrimitives) return;

            osg::Vec3Array *coords = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());
            _vertexArrays.push_back(coords);

            //osg::Vec3Array *normals = dynamic_cast<osg::Vec3Array*>(geom->getNormalArray());
        }

//        AttributePrinter attrPrinter;
//        drawable->accept(attrPrinter);

//        osg::TriangleFunctor<TrianglePrinter> triPrinter;
//        drawable->accept(triPrinter);

//        std::cout << std::endl;
    }
    traverse(node);
}
