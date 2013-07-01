MESSAGE(STATUS "Importing OpenCV...")

OPTION(OTB_USE_OPENCV "Use OpenCV library for classification." OFF)
MARK_AS_ADVANCED(OTB_USE_OPENCV)

IF(OTB_USE_OPENCV)
  MESSAGE(STATUS "  Enabling OpenCV support")
  FIND_PACKAGE(OpenCV
               REQUIRED
               PATHS
                 /opt/local/lib/cmake # MacPort
               )
  MESSAGE(STATUS "  Found OpenCV ${OpenCV_VERSION_MAJOR}.${OpenCV_VERSION_MINOR}.${OpenCV_VERSION_PATCH}")
  MESSAGE(STATUS "  OpenCV include directory: ${OpenCV_INCLUDE_DIRS}")
ELSE()
  MESSAGE(STATUS "  Disabling OpenCV support (OTB_USE_OPENCV is OFF)")
ENDIF()