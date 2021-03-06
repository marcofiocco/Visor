set(OSG_ROOT_DIR ""  CACHE PATH "OSG_ROOT_DIR")
set(OSG_DATA_DIR ""  CACHE PATH "OSG_DATA_DIR")
set(OSG_PLUGINS_DIR ""  CACHE PATH "OSG_PLUGINS_DIR")

IF("${OSG_ROOT_DIR}" STREQUAL "")

    message(FATAL_ERROR "Could not find OSG_ROOT_DIR: ${OSG_ROOT_DIR}")

ENDIF("${OSG_ROOT_DIR}" STREQUAL "")

set(OSG_INCLUDE_DIR "${OSG_ROOT_DIR}/include"  CACHE PATH "OSG_INCLUDE_DIR")
set(OSG_LIB_DIR "${OSG_ROOT_DIR}/lib"  CACHE PATH "OSG_LIB_DIR")
set(OSG_BIN_DIR "${OSG_ROOT_DIR}/bin"  CACHE PATH "OSG_BIN_DIR")

IF(NOT IS_DIRECTORY ${OSG_INCLUDE_DIR})

    message(FATAL_ERROR "Could not find OSG_INCLUDE_DIR: ${OSG_INCLUDE_DIR}")

ENDIF(NOT IS_DIRECTORY ${OSG_INCLUDE_DIR})

IF(NOT IS_DIRECTORY ${OSG_LIB_DIR})

    message(FATAL_ERROR "Could not find OSG_LIB_DIR: ${OSG_LIB_DIR}")

ENDIF(NOT IS_DIRECTORY ${OSG_LIB_DIR})

IF(NOT IS_DIRECTORY ${OSG_BIN_DIR})

    message(FATAL_ERROR "Could not find OSG_BIN_DIR: ${OSG_BIN_DIR}")

ENDIF(NOT IS_DIRECTORY ${OSG_BIN_DIR})


IF("${OSG_DATA_DIR}" STREQUAL "")

    message(FATAL_ERROR "Could not find OSG_DATA_DIR: ${OSG_DATA_DIR}")
    
    IF(NOT IS_DIRECTORY ${OSG_DATA_DIR})

    message(FATAL_ERROR "Could not find OSG_INCLUDE_DIR: ${OSG_DATA_DIR}")

    ENDIF(NOT IS_DIRECTORY ${OSG_DATA_DIR})
    
ENDIF("${OSG_DATA_DIR}" STREQUAL "")

IF("${OSG_PLUGINS_DIR}" STREQUAL "")

    message(FATAL_ERROR "Could not find OSG_PLUGINS_DIR: ${OSG_PLUGINS_DIR}")
    
    IF(NOT IS_DIRECTORY ${OSG_DATA_DIR})

    message(FATAL_ERROR "Could not find OSG_PLUGINS_DIR: ${OSG_PLUGINS_DIR}")

  ENDIF(NOT IS_DIRECTORY ${OSG_PLUGINS_DIR})

ENDIF("${OSG_PLUGINS_DIR}" STREQUAL "")