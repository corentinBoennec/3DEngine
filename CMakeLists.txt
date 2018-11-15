cmake_minimum_required(VERSION 3.6)

set(GLUT_INCLUDE_DIR "extlibs/freeglut/include")
set(GLUT_glut_LIBRARY "extlibs/freeglut/lib/x64/freeglut")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

project(3DEngine)

include(group_files)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

file(GLOB_RECURSE 3DENGINE_HEADERS 
    ${3DEngine_SOURCE_DIR}/include/*.hpp 
    ${3DEngine_SOURCE_DIR}/include/*.inl)
file(GLOB_RECURSE 3DENGINE_SOURCES ${3DEngine_SOURCE_DIR}/src/*.cpp)

add_executable(3DEngine ${3DENGINE_HEADERS} ${3DENGINE_SOURCES})


target_include_directories(3DEngine
    PUBLIC 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	${GLUT_INCLUDE_DIR}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(3DEngine ${GLUT_glut_LIBRARY})

group_files(
    "${3DENGINE_HEADERS}" "${3DENGINE_SOURCES}"
    "${3DEngine_SOURCE_DIR}"
    "${3DEngine_SOURCE_DIR}"
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
endif (MSVC)