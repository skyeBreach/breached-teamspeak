#----------------------------------------------------------------------------------------------------------------------#
# CMake Versioning

# TODO: IDk if this is fully true
# Set CMake to use version 3.21, as it is the highest version Qt allows
cmake_minimum_required(VERSION 3.21)

# Ensures that all source files have their extensions explicitly listed, as this is the new behavior of CMake
if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.20")
	cmake_policy(SET CMP0115 NEW)
endif()

#----------------------------------------------------------------------------------------------------------------------#
# Qt UI Library 

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set all CMake Qt auto flags to true
set(CMAKE_AUTOMOC ON)

# Find an load the Qt libraries
find_package(Qt5 COMPONENTS Core Widgets REQUIRED )

# If we found Qt then load it, and if not we must abort and call a fatal
if(${Qt5_FOUND})
    message(VERBOSE "Found Qt " ${Qt5_VERSION})
    link_libraries(Qt5::Core Qt5::Widgets)
else()
    message(
        FATAL_ERROR 
        "The Qt libraries could not be found, Make sure that your QT_PATH is properly set. Aborting as Qt is required!"
    )
endif(${Qt5_FOUND})

#----------------------------------------------------------------------------------------------------------------------#
# Package Directories

# Assign include directories
include_directories(
    "${CMAKE_CURRENT_LIST_DIR}/libs/ts3client-pluginsdk/include"
    "${CMAKE_CURRENT_LIST_DIR}/include"
)

# Store all of the packages source files in a variable and assign these to there own source_group
set(BREACHED_TS_SRC
    ${CMAKE_CURRENT_LIST_DIR}/include/breached-teamspeak/plugin.h
    ${CMAKE_CURRENT_LIST_DIR}/src/plugin.cpp
)

#----------------------------------------------------------------------------------------------------------------------#