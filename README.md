Visor is an simple OpenSceneGraph project to create a 3D rendering window for your projects.
It allows to quickly setup a framework to test your 3D models (using the many file format plugins provided by OSG) and render them while getting access also to the internal geometry and code model processing.

The following are instructions to compile for macOS but it's relatively easy to compile also for Windows and Linux, given that the project is based on CMake and Qt.

COMPILING FROM SCRATCH FOR macOS

- Install CMake (tested with 3.3.1): http://www.cmake.org/download/

- Install Qt (tested with Qt 5.5): http://www.qt.io/qt5-5/

- Install ‘brew’: http://brew.sh/

- Run ‘brew install jpeg’

- Run ’brew install freetype’

- Download OpenSceneGraph source and data(tested with 3.4.0)
	- http://www.openscenegraph.org/index.php/download-section/stable-releases
	- http://www.openscenegraph.org/downloads/stable_releases/OpenSceneGraph-3.4.0/data/OpenSceneGraph-Data-3.4.0.zip

- Run OSG CMakeFile.txt in CMake and compile with ‘makefile’ target, set
	- Qt5Widgets_DIR to \<your Qt install dir\>/5.5/clang_64/lib/cmake/Qt5Widgets

- Run ‘make -j4’ in the build dir of OSG

- Run ‘sudo make install’

- Run Visor CMakeFile.txt in CMake and compile with ‘makefile’ target, set
	- Qt5Widgets_DIR to \<your Qt install dir\>/5.5/clang_64/lib/cmake/Qt5Widgets
	- OSG_ROOT_DIR = /usr/local
	- OSG_PLUGINS_DIR = /usr/local/lib/osgPlugins-3.4.0
	- OSG_DATA_DIR = \<your OSG data install dir\>/OpenSceneGraph-Data-3.4.0

- compile with ‘make -j4’ in the build dir of Visor

- Run:
‘export OSG_FILE_PATH=\<your OSG data install dir\>/OpenSceneGraph-Data-3.4.0’

- Run ‘./Visor’

- You can also write and debug code in QtCreator, just open the project by loading the CMakeFile.txt of Visor and then go into Projects, select the Run tab and add the Run Environment variable OSG_FILE_PATH to the value \<your OSG data install dir\>/OpenSceneGraph-Data-3.4.0
