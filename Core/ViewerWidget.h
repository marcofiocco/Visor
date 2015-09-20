#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H

#include"Core_global.h"

#include <QTimer>
#include <QApplication>
#include <QGridLayout>

#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgGA/MultiTouchTrackballManipulator>

#include <osgDB/ReadFile>

#include <osgQt/GraphicsWindowQt>

#include <iostream>

class CORE_EXPORT ViewerWidget : public QWidget, public osgViewer::CompositeViewer
{
public:
    ViewerWidget(QWidget* parent = 0, Qt::WindowFlags f = 0, osgViewer::ViewerBase::ThreadingModel threadingModel=osgViewer::CompositeViewer::SingleThreaded);

    QWidget* addViewWidget( osgQt::GraphicsWindowQt* gw, osg::Node* scene );

    osgQt::GraphicsWindowQt* createGraphicsWindow( int x, int y, int w, int h, const std::string& name="", bool windowDecoration=false );

    virtual void paintEvent( QPaintEvent* event );

protected:

    QTimer _timer;
};

#endif // VIEWERWIDGET_H
