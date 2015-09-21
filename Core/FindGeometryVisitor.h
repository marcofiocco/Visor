#ifndef FINDGEOMETRYVISITOR_H
#define FINDGEOMETRYVISITOR_H

#include"Core_global.h"
#include <osg/NodeVisitor>

class CORE_EXPORT FindGeometryVisitor : public osg::NodeVisitor
{
public:
    FindGeometryVisitor();

    virtual void apply(osg::Node& node);
    virtual void apply(osg::Geode& node);

    const std::vector<osg::Vec3Array*>& vertexArrays() const { return _vertexArrays; }

protected:
    std::vector<osg::Vec3Array*> _vertexArrays;
};

#endif // FINDGEOMETRYVISITOR_H
