
cmake_minimum_required(VERSION 3.21)

#----------------------------------------------------------------------------------------------------------------------#
# Qt UI Library 

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set all CMake Qt auto flags to true
set(CMAKE_AUTOMOC ON)

# Defines the paths for Qt, so CMake knows where it is
set(QT_PATH "C:/Qt")
set(QT_ENV_PATH "${QT_PATH}/6.8.1/msvc2022_64")

# Displays the paths we have just set in console (if in verbose)
message(Verbose "QT Path: ${QT_PATH}")
message(Verbose "QT Env : ${QT_ENV_PATH}")

# Add a prefix path for the correct Qt install
set(CMAKE_PREFIX_PATH ${QT_ENV_PATH})

# Find an load the Qt libraries
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# If we found Qt then load it, and if not we must abort and call a fatal
if(${Qt6_FOUND})
    message(Verbose "Found Qt " ${Qt6_VERSION})
    link_libraries(Qt6::Core Qt6::Widgets)
else()
    message(
        FATAL_ERROR 
        "The Qt libraries could not be found, Make sure that your QT_PATH is properly set. Aborting as Qt is required!"
    )
endif(${Qt6_FOUND})

#----------------------------------------------------------------------------------------------------------------------#
# Package Directories

# Assign include directories
include_directories(
    "${CMAKE_CURRENT_LIST_DIR}/libs/ts3client-pluginsdk/include"
    "${CMAKE_CURRENT_LIST_DIR}/include/breached-teamspeak"
    "${CMAKE_CURRENT_LIST_DIR}/src"
)

# Store all of the packages source files in a variable and assign these to there own source_group
set(BREACHED_TS_SRC
    ${CMAKE_CURRENT_LIST_DIR}/src/breached-plugin.h
    ${CMAKE_CURRENT_LIST_DIR}/src/breached-plugin.cpp
)
source_group("Breached Teamspeak" FILES ${BREACHED_TS_SRC})

#----------------------------------------------------------------------------------------------------------------------#