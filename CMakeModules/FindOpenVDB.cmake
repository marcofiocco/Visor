#   Find OpenVDB headers and libraries.
#
#  This module defines
#  OpenVDB_INCLUDE_DIRS - where to find openvdb includes.
#  OpenVDB_LIBRARIES    - List of libraries when using openvdb.
#  OpenVDB_FOUND        - True if openvdb found.

# Look for the header file.
FIND_PATH( OPENVDB_INCLUDE_DIR NAMES openvdb/openvdb.h)

# Look for the library.
FIND_LIBRARY( OPENVDB_LIBRARY NAMES openvdb)

# handle the QUIETLY and REQUIRED arguments and set OPENVDB_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE( FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS( OPENVDB DEFAULT_MSG OPENVDB_LIBRARY OPENVDB_INCLUDE_DIR)

# compilation flags
SET( OPENVDB_COMPILE_FLAGS)

# Copy the results to the output variables.
IF( OPENVDB_FOUND)
    SET( OPENVDB_LIBRARIES ${OPENVDB_LIBRARY})
    SET( OPENVDB_INCLUDE_DIRS ${OPENVDB_INCLUDE_DIR})
ELSE()
    SET( OPENVDB_LIBRARIES)
    SET( OPENVDB_INCLUDE_DIRS)
ENDIF()

MARK_AS_ADVANCED( OPENVDB_INCLUDE_DIR OPENVDB_LIBRARY)
