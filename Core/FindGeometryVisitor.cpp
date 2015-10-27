#include "FindGeometryVisitor.h"
#include <osg/Drawable>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/TriangleFunctor>
#include <osg/io_utils>
#include <iostream>

using namespace Visor;

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

        osg::Geometry* osg_geom = dynamic_cast<osg::Geometry*>(drawable);
        if (osg_geom)
        {
            Visor::Geometry geometry(osg_geom);
            _geometryArray.push_back(geometry);
        }

//        AttributePrinter attrPrinter;
//        drawable->accept(attrPrinter);

//        osg::TriangleFunctor<TrianglePrinter> triPrinter;
//        drawable->accept(triPrinter);

//        std::cout << std::endl;
    }
    traverse(node);
}

Primitive::Primitive(const osg::PrimitiveSet *primitive)
{
    type = (osg::PrimitiveSet::Mode)primitive->getMode();
    for (int i = 0; i < primitive->getNumIndices(); ++i)
    {
        indices.push_back(primitive->index(i));
    }
}

osg::PrimitiveSet::Mode Primitive::getType() const
{
    return type;
}

const std::vector<uint>& Primitive::getIndices() const
{
    return indices;
}

Geometry::Geometry(const osg::Geometry *osg_geometry)
{
    const osg::Geometry::PrimitiveSetList& osg_primitives = osg_geometry->getPrimitiveSetList();
    for (int p = 0; p < osg_primitives.size(); ++p)
    {
        osg::PrimitiveSet* osg_primitive = osg_primitives[p];
        switch(osg_primitive->getMode())
        {
            case(osg::PrimitiveSet::TRIANGLES):
            case(osg::PrimitiveSet::TRIANGLE_STRIP):
            case(osg::PrimitiveSet::TRIANGLE_FAN):
            case(osg::PrimitiveSet::QUADS):
            case(osg::PrimitiveSet::QUAD_STRIP):
            case(osg::PrimitiveSet::POLYGON):
                {
                    Visor::Primitive visor_primitive(osg_primitive);
                    _primitiveArray.push_back(visor_primitive);
                }

                break;
            default:
                break;
        }
    }

    if (_primitiveArray.size() == 0)
        return;

    const osg::Vec3Array *coords = dynamic_cast<const osg::Vec3Array*>(osg_geometry->getVertexArray());
    for (int v = 0; v < coords->size(); ++v)
    {
        _vertexArray.push_back(Visor::Vertex(coords->at(v)));
    }

    //osg::Vec3Array *normals = dynamic_cast<osg::Vec3Array*>(osg_geometry->getNormalArray());
}

Vertex::Vertex(const osg::Vec3 &v)
{
    _v[0] = v.x();
    _v[1] = v.y();
    _v[2] = v.z();
}
