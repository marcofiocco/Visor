PROJECT(Tests)

# Test stuff
# CMake will generate tests only if the enable_testing() command has been invoked. The CTest module invokes the command automatically when the BUILD_TESTING option is ON
ENABLE_TESTING()

FIND_PACKAGE(Qt5Test REQUIRED)

FIND_PACKAGE(CGAL COMPONENTS Core)
IF (CGAL_FOUND)
  INCLUDE(${CGAL_USE_FILE})
ELSE()
  MESSAGE(STATUS "This test requires the CGAL library, and will not be compiled.")
ENDIF()

FIND_PACKAGE(OpenVDB)
INCLUDE_DIRECTORIES (${OPENVDB_INCLUDE_DIR})

MACRO (addTest testname testsrc)
  SET (test_${testname}_SRCS ${testsrc})
  ADD_EXECUTABLE(test_${testname} ${test_${testname}_SRCS})
  TARGET_LINK_LIBRARIES(test_${testname} Qt5::Test Core ${OPENVDB_LIBRARY})
  ADD_TEST(test_${testname} test_${testname})
ENDMACRO (addTest)

addTest(BasicTest tst_basictest.cpp)
addTest(CGALTest tst_test_cgal.cpp)

# OpenVDB on MacOSX (downloaded with 'brew') says symbol(s) not found for architecture x86_64, when linking here. Must recompile OpenVDB from scratch?
#addTest(OpenVDBTest tst_test_openvdb.cpp)
