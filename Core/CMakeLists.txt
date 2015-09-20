PROJECT(Core)

# Find the QtWidgets library, check http://doc.qt.io/qt-5/cmake-manual.html
FIND_PACKAGE(Qt5Widgets REQUIRED)

SET(TARGET_H
    Core_global.h
    GeometryImporter.h
    ViewerWidget.h
)

SET(TARGET_SRC
    GeometryImporter.cpp
    ViewerWidget.cpp
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${${TARGET_H}} ${TARGET_SRC})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} OpenThreads osg osgDB osgViewer osgGA osgWidget osgQt)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} Qt5::Widgets)

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES DEFINE_SYMBOL ${PROJECT_NAME_CAPITALIZED}_LIBRARY)

IF (Qt5Widgets_FOUND)
    QT5_USE_MODULES(${PROJECT_NAME} Widgets OpenGL)
ENDIF(Qt5Widgets_FOUND)
