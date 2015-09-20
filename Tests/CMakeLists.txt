PROJECT(Tests)

# Test stuff
# CMake will generate tests only if the enable_testing() command has been invoked. The CTest module invokes the command automatically when the BUILD_TESTING option is ON
ENABLE_TESTING()

FIND_PACKAGE(Qt5Test REQUIRED)

MACRO (addTest testname testsrc)
  SET (test_${testname}_SRCS ${testsrc})
  ADD_EXECUTABLE(test_${testname} ${test_${testname}_SRCS})
  TARGET_LINK_LIBRARIES(test_${testname} Qt5::Test Core)
  ADD_TEST(test_${testname} test_${testname})
ENDMACRO (addTest)

addTest(BasicTest tst_basictest.cpp)
