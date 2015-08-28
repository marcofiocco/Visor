PROJECT(Visor)
CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

# Find includes in corresponding build directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
SET(CMAKE_AUTOMOC ON)

# Find the QtWidgets library, check http://doc.qt.io/qt-5/cmake-manual.html
FIND_PACKAGE(Qt5Widgets REQUIRED)

FIND_PACKAGE(OSG REQUIRED)
INCLUDE_DIRECTORIES(${OSG_INCLUDE_DIR})
LINK_DIRECTORIES(${OSG_LIB_DIR})

SET( TARGET_SRC
    osgviewerQt.cpp
)

ADD_EXECUTABLE(${PROJECT_NAME} WIN32 ${TARGET_SRC} ${TARGET_H})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} OpenThreads osg osgDB osgViewer osgGA osgWidget osgQt)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} Qt5::Widgets)

IF ( Qt5Widgets_FOUND )
    QT5_USE_MODULES(${PROJECT_NAME} Widgets OpenGL)
ENDIF( Qt5Widgets_FOUND )

