cmake_minimum_required(VERSION 3.0.0)

if (POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()

if (POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()

set (MAJOR_VERSION 0)
set (MINOR_VERSION 1)
set (PATCH_VERSION 0)
project(SpFoundation VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})

set (PROJECT_DIR  ${CMAKE_CURRENT_SOURCE_DIR})
set (SOLUTION_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

option(OPERATING_SYSTEM "Defined which operating system will be built for" "WINDOWS")
option(ARCH_BITS        "Defined the compilation to 64 bits"   "64")
option(GLFW_ENABLED     "Defined if GLFW will be used" ON)
option(QT_ENABLED       "Defined if QT will be used"   OFF)

set (GLFW_DEFINITION "")
set (QT_DEFINITION   "")

set (CMAKE_C_STANDARD 11)
set (CMAKE_C_STANDARD_REQUIRED ON)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

if ( ${ARCH_BITS} STREQUAL "64" )
	set (ARCH "x86_64")
	set (CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -m64 -fPIC -std=c11" )
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -fPIC -std=c++11" )
else()
	set(ARCH "x86")	
	set (CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -m32 -fPIC -std=c11" )
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32 -fPIC -std=c++11" )
endif()

if ( ${OPERATING_SYSTEM} STREQUAL "WINDOWS" )

	if( ${BUILD_SHARED_LIBS} )
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
	else()
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
	endif()

    set (GLFW_LIB_NAME "glfw3.lib")
	set (CUSTOM_DEFINITIONS "-D_CRT_SECURE_NO_WARNINGS")
elseif ( ${OPERATING_SYSTEM} STREQUAL "LINUX" OR ${OPERATING_SYSTEM} STREQUAL "UNIX" )
    set (GLFW_LIB_NAME "libglfw3.a")
	set (CUSTOM_DEFINITIONS "-Wno-dangling-else")
else()
    message(FATAL_ERROR "Operating System not defined!")
endif()

find_package(OpenGL REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)

file(GLOB HEADERS "src/*.h")
file(GLOB SOURCES "src/*.cpp")

if ( ${GLFW_ENABLED} )
    list(FILTER SOURCES EXCLUDE REGEX ".*QT.cpp$") #remove QT files
	set (GLFW_DEFINITION "-DGLFW_ENABLED")
endif()
if( ${QT_ENABLED} )
    list(FILTER SOURCES EXCLUDE REGEX ".*GLFW.cpp$") #remove GLFW files
	set (QT_DEFINITION   "-QT_ENABLED")
endif()

include_directories(
    /usr/local/include
	${SOLUTION_DIR}/vendor/glfw/include
    src
)

link_directories(
	${SOLUTION_DIR}/vendor/lib/x86_64
	${SOLUTION_DIR}/vendor/lib
	/usr/local/lib/
)

if(BUILD_SHARED_LIBS)
	add_library(${PROJECT_NAME} SHARED ${SOURCES})
else()
	add_library(${PROJECT_NAME} STATIC ${SOURCES})
endif()

if ( ${OPERATING_SYSTEM} STREQUAL "WINDOWS" )
    add_definitions(-DENV_64BITS -DAPI_EXPORT ${CUSTOM_DEFINITIONS} -DWINDOWS)
elseif ( ${OPERATING_SYSTEM} STREQUAL "LINUX" )
    add_definitions(-DENV_64BITS -DAPI_EXPORT ${CUSTOM_DEFINITIONS} -DLINUX)
elseif ( ${OPERATING_SYSTEM} STREQUAL "UNIX" )
    add_definitions(-DENV_64BITS -DAPI_EXPORT ${CUSTOM_DEFINITIONS} -DUNIX)
else()
    message(FATAL_ERROR "Operating System not defined!")
endif()

target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARY}
    ${SOLUTION_DIR}/vendor/lib/${GLFW_LIB_NAME}
)
