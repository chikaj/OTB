
include(External_glew)

if(BUILD_ICE_APPLICATION)
  include(External_glfw)
  include(External_glut)
endif()

message(STATUS "Setup Ice...")

set(proj ICE)

set(ICE_SB_SRC ${CMAKE_BINARY_DIR}/${proj}/src/${proj})
set(ICE_SB_BUILD_DIR ${CMAKE_BINARY_DIR}/${proj}/build)

set(${proj}_DEPENDENCIES OTB)

#need this var anyway for cmake_cache_args
set(ICE_SB_GLFW_CONFIG)

if(BUILD_ICE_APPLICATION)
  if(USE_SYSTEM_GLFW)
    set(ICE_SB_GLFW_CONFIG)
  else()
    set(ICE_SB_GLFW_CONFIG
      -DGLFW_INCLUDE_DIR:PATH={CMAKE_INSTALL_PREFIX}/include
      -DGLFW_LIBRARY:FILEPATH=${CMAKE_INSTALL_PREFIX}/lib/glfw.so)  
    list(APPEND ${proj}_DEPENDENCIES GLFW)
  endif()
endif()

if(USE_SYSTEM_GLEW)
  set(ICE_SB_GLEW_CONFIG)
else()
  set(ICE_SB_GLEW_CONFIG
    -DGLEW_INCLUDE_DIR:PATH={CMAKE_INSTALL_PREFIX}/include
    -DGLEW_LIBRARY:FILEPATH=${CMAKE_INSTALL_PREFIX}/lib/glew.so)
  list(APPEND ${proj}_DEPENDENCIES GLEW)
endif()


if(USE_SYSTEM_ITK)
  set(ICE_SB_ITK_CONFIG)
else()
  set(ICE_SB_ITK_CONFIG
    -DITK_DIR:PATH=${CMAKE_INSTALL_PREFIX}/lib/cmake/ITK-4.6)
  list(APPEND ${proj}_DEPENDENCIES ITK)
endif()

if(USE_SYSTEM_TINYXML)
  set(ICE_SB_TINYXML_CONFIG)
else()
  set(ICE_SB_TINYXML_CONFIG
    -DTINYXML_INCLUDE_DIR:PATH=${CMAKE_INSTALL_PREFIX}/include
    -DTINYXML_LIBRARY:PATH=${CMAKE_INSTALL_PREFIX}/lib/libtinyXML${CMAKE_SHARED_LIBRARY_SUFFIX}
    )
  list(APPEND ${proj}_DEPENDENCIES TINYXML)
endif()

if(MSVC)
  set(ICE_SB_ITK_CONFIG)
  set(ICE_SB_GLEW_CONFIG)
  set(ICE_SB_GLFW_CONFIG)
endif()

ExternalProject_Add(${proj}
   DEPENDS ${${proj}_DEPENDENCIES}
   PREFIX ${proj}
   HG_REPOSITORY "http://hg.orfeo-toolbox.org/Ice"
   HG_TAG tip
   BINARY_DIR ${ICE_SB_BUILD_DIR}
   INSTALL_DIR ${CMAKE_INSTALL_PREFIX}
   DEPENDS ${${proj}_DEPENDENCIES}    
   CMAKE_CACHE_ARGS
    -DCMAKE_INSTALL_PREFIX:STRING=${CMAKE_INSTALL_PREFIX}
    -DCMAKE_BUILD_TYPE:STRING=Release
    -DBUILD_SHARED_LIBS:BOOL=${SB_BUILD_SHARED_LIBS}
    -DBUILD_TESTING:BOOL=${BUILD_TESTING}
    -DBUILD_ICE_APPLICATION:BOOL=${BUILD_ICE_APPLICATION}
    -DOTB_DIR:PATH=${CMAKE_INSTALL_PREFIX}/lib/otb
    ${ICE_SB_ITK_CONFIG}
    ${ICE_SB_GLFW_CONFIG}
    ${ICE_SB_GLEW_CONFIG}
    ${ICE_SB_TINYXML_CONFIG}
   )

message(STATUS "  Using Ice SuperBuild version")
