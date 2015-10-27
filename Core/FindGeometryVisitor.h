#ifndef FINDGEOMETRYVISITOR_H
#define FINDGEOMETRYVISITOR_H

#include"Core_global.h"
#include <osg/NodeVisitor>
#include <osg/PrimitiveSet>

namespace Visor {

class Vertex {
public:
    Vertex(const osg::Vec3 &v);
    const float* pointer() const { return _v; }
    float x() const { return _v[0]; }
    float y() const { return _v[1]; }
    float z() const { return _v[2]; }
private:
    float _v[3];
};

class Primitive {
public:
    Primitive(const osg::PrimitiveSet* primitive);

    osg::PrimitiveSet::Mode getType() const;
    const std::vector<uint>& getIndices() const;

private:
    osg::PrimitiveSet::Mode type;
    std::vector<uint> indices;
};

class Geometry {
public:
    Geometry(const osg::Geometry* geometry);

    const std::vector<Visor::Vertex>& vertexArray() const { return _vertexArray; }
    const std::vector<Visor::Primitive>& primitiveArray() const { return _primitiveArray; }

private:
    std::vector<Visor::Vertex> _vertexArray;
    std::vector<Visor::Primitive> _primitiveArray;
};

class CORE_EXPORT FindGeometryVisitor : public osg::NodeVisitor
{
public:
    FindGeometryVisitor();

    virtual void apply(osg::Node& node);
    virtual void apply(osg::Geode& node);

    const std::vector<Visor::Geometry>& geometryArray() const { return _geometryArray; }

protected:
    std::vector<Visor::Geometry> _geometryArray;
};

}

#endif // FINDGEOMETRYVISITOR_H
