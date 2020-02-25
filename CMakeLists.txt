cmake_minimum_required(VERSION 3.0.0)
project(SpFoundation VERSION 0.1.0)

set (CMAKE_C_STANDARD 11)
set (CMAKE_C_STANDARD_REQUIRED ON)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(GLFW3  REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)

file(GLOB HEADERS "src/*.h")
file(GLOB SOURCES "src/*.cpp")
#list(FILTER SOURCES EXCLUDE REGEX ".*QT.cpp$")

INCLUDE_DIRECTORIES(
    /usr/local/include/
    ${HEADERS}
)

link_directories(
	/usr/local/lib/
)

add_library(SpFoundation 
    ${SOURCES}
)

add_definitions(-DUNIX -DENV_32BITS -DGLFW -Wno-dangling-else)

target_link_libraries(SpFoundation
    ${OPENGL_LIBRARY}
    glfw3
)
