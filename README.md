COMPILING FROM SCRATCH IN MACOSX

- Install CMake (tested with 3.3.1): http://www.cmake.org/download/

- Install Qt (tested with Qt 5.5): http://www.qt.io/qt5-5/

- Install ‘brew’: http://brew.sh/

- Run ‘brew install jpeg’

- Run ’brew install freetype’

- Download OpenSceneGraph (tested with 3.4.0): http://www.openscenegraph.org/index.php/download-section/stable-releases

- Run OSG CMakeFile in CMake and compile with ‘makefile’ target, set
	- Qt5Widgets_DIR to /Users/marcofiocco/Qt/5.5/clang_64/lib/cmake/Qt5Widgets

- Run ‘make -j4’ in the build dir of OSG

- Run ‘sudo make install’

- Run Visor CMakeFile in CMake and compile with ‘makefile’ target, set
	- Qt5Widgets_DIR to /Users/marcofiocco/Qt/5.5/clang_64/lib/cmake/Qt5Widgets
	- OSG_ROOT_DIR = /usr/local
	- OSG_PLUGINS_DIR = /usr/local/lib/osgPlugins-3.4.0
	- OSG_DATA_DIR = /Users/marcofiocco/Documents/Code/Spacesuit/OpenSceneGraph-Data-3.4.0

- compile with ‘make -j4’ in the build dir of Visor

- Run:
export OSG_FILE_PATH=/Users/marcofiocco/Documents/Code/Spacesuit/OpenSceneGraph-Data-3.4.0 

- Run ‘./Visor’