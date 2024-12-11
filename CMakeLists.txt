#----------------------------------------------------------------------------------------------------------------------#
# CMake Setup

# TODO: IDk if this is fully true
# Set CMake to use version 3.21, as it is the highest version Qt allows
cmake_minimum_required(VERSION 3.21)

# Run all config safe guards
include("${CMAKE_CURRENT_LIST_DIR}/cmake/modules/SafeGuard.cmake")

#----------------------------------------------------------------------------------------------------------------------#
# VCPKG Setup

# Set the toolchain file to "vcpkg.cmake", based off of a filepath normalized VCPKG_ROOT
file(TO_CMAKE_PATH "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CMAKE_TOOLCHAIN_FILE)

#----------------------------------------------------------------------------------------------------------------------#
# Project Definition

# Read the config metadata JSON file 
file(READ ${CMAKE_CURRENT_LIST_DIR}/config/library.json PLUGIN_DATA_JSON)
string(JSON PROJECT_NAME            GET ${PLUGIN_DATA_JSON} name)
string(JSON PROJECT_VERSION         GET ${PLUGIN_DATA_JSON} version)
string(JSON PROJECT_LABEL           GET ${PLUGIN_DATA_JSON} label)
string(JSON PROJECT_DESCRIPTION     GET ${PLUGIN_DATA_JSON} description)
string(JSON PROJECT_HOMEPAGE_URL    GET ${PLUGIN_DATA_JSON} homepage)

# Set the project based off of the config file
project(
    ${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
    DESCRIPTION ${PROJECT_DESCRIPTION}
    HOMEPAGE_URL ${PROJECT_HOMEPAGE_URL}
	LANGUAGES CXX
)

#----------------------------------------------------------------------------------------------------------------------#
# Dependency Config

find_package(Boost COMPONENTS log REQUIRED)
link_libraries(boost::log)

#----------------------------------------------------------------------------------------------------------------------#
# Qt UI Library 

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set all CMake Qt auto flags to true
set(CMAKE_AUTOMOC ON)

# Start a "check message" block for the Qt lib search, and ensure block messages are indented
message(
    CHECK_START
    "Attempting to find Qt"
)
list(APPEND CMAKE_MESSAGE_INDENT "  ")

# Find an load the Qt libraries
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# If we found Qt then load it, and if not we must abort and call a fatal
if(${Qt5_FOUND})
    link_libraries(Qt5::Core Qt5::Widgets)
    message(
        CHECK_PASS 
        "Qt v" ${Qt5_VERSION} " found, and has been linked"
    )
else()
    message(
        CHECK_FAIL 
        "The Qt libraries could not be found, Make sure that your QT_PATH is properly set. Aborting as Qt is required!"
    )
endif(${Qt5_FOUND})

# Remove message indentation
list(POP_BACK CMAKE_MESSAGE_INDENT)

#----------------------------------------------------------------------------------------------------------------------#
# Library Source and Include Files

# Assign include directories
include_directories(
    "${CMAKE_CURRENT_LIST_DIR}/libs/ts3client-pluginsdk/include"
    "${CMAKE_CURRENT_LIST_DIR}/include"
)
 
# Store all of the packages source files in a variable and assign these to there own source_group
set(BREACHED_TS_SRC
    ${CMAKE_CURRENT_LIST_DIR}/include/breached-teamspeak/core/plugin.h
    ${CMAKE_CURRENT_LIST_DIR}/src/core/plugin.cpp
    ${CMAKE_CURRENT_LIST_DIR}/include/breached-teamspeak/teamspeak.h
    ${CMAKE_CURRENT_LIST_DIR}/src/teamspeak.cpp
)

#----------------------------------------------------------------------------------------------------------------------#