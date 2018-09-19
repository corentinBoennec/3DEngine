cmake_minimum_required(VERSION 3.6)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

project(3DEngine)

add_subdirectory(extlibs/glfw)

find_package(OpenGL REQUIRED)

file(GLOB 3DENGINE_HEADERS include/*.hpp)
file(GLOB 3DENGINE_SOURCES src/*.cpp)

add_executable(3DEngine ${3DENGINE_HEADERS} ${3DENGINE_SOURCES})

target_link_libraries(3DEngine glfw)

target_include_directories(3DEngine
    PUBLIC 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	${GLUT_INCLUDE_DIR}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)


set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
endif (MSVC)