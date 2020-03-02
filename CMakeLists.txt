cmake_minimum_required(VERSION 3.0.0)
cmake_policy(SET CMP0054 NEW)

set (MAJOR_VERSION 0)
set (MINOR_VERSION 1)
set (PATCH_VERSION 0)
project(SpFoundation VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})

option(OPERATING_SYSTEM "Defined which operating system will be built for" "WINDOWS")
option(GLFW_ENABLED     "Defined if GLFW will be used" ON)
option(QT_ENABLED       "Defined if QT will be used"   OFF)

set (CMAKE_C_STANDARD 11)
set (CMAKE_C_STANDARD_REQUIRED ON)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

if ( ${OPERATING_SYSTEM} STREQUAL "WINDOWS" )
    set (GLFW_LIB_NAME "glfw3.lib")
elseif ( ${OPERATING_SYSTEM} STREQUAL "LINUX" OR ${OPERATING_SYSTEM} STREQUAL "UNIX" )
    set (GLFW_LIB_NAME "libglfw3.a")
else()
    message(FATAL_ERROR "Operating System not defined!")
endif()

find_package(OpenGL REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)

file(GLOB HEADERS "src/*.h")
file(GLOB SOURCES "src/*.cpp")

if ( ${GLFW_ENABLED} )
    list(FILTER SOURCES EXCLUDE REGEX ".*QT.cpp$") #remove QT files
elseif( ${QT_ENABLED} )
    list(FILTER SOURCES EXCLUDE REGEX ".*GLFW.cpp$") #remove GLFW files
else()
    message(FATAL_ERROR "One of windowing library must be set at least (GLFW or QT).")
endif()

include_directories(
    /usr/local/include
	../vendor/glfw/include
    src
)

link_directories(
	/usr/local/lib/
)

add_library(SpFoundation ${SOURCES})

if ( ${OPERATING_SYSTEM} STREQUAL "WINDOWS" )
    add_definitions(-DENV_32BITS -DGLFW_ENABLED -Wno-dangling-else -DWINDOWS)
elseif ( ${OPERATING_SYSTEM} STREQUAL "LINUX" )
    add_definitions(-DENV_32BITS -DGLFW_ENABLED -Wno-dangling-else -DLINUX)
elseif ( ${OPERATING_SYSTEM} STREQUAL "UNIX" )
    add_definitions(-DENV_32BITS -DGLFW_ENABLED -Wno-dangling-else -DUNIX)
else()
    message(FATAL_ERROR "Operating System not defined!")
endif()

target_link_libraries(SpFoundation
    ${OPENGL_LIBRARY}
    ../vendor/lib/${GLFW_LIB_NAME}
)
