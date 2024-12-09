#----------------------------------------------------------------------------------------------------------------------#
# CMake Versioning

# Set CMake to use version 3.21, as it is the highest version Qt allows
cmake_minimum_required(VERSION 3.21)

# Ensures that all source files have their extensions explicitly listed, as this is the new behavior of CMake
if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.20")
	cmake_policy(SET CMP0115 NEW)
endif()

#----------------------------------------------------------------------------------------------------------------------#
# Package/Library Guards

# Enforce a global include guard here, this may not be needed now but may be in future
include_guard(GLOBAL)

# Make sure that the build or configure command hasn't been called at the root directory
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
        FATAL_ERROR
            "Builds can not be run from the src directory. You must make a build directory and run CMake from there."
    )
endif()



#----------------------------------------------------------------------------------------------------------------------#
# Qt UI Library 

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Defines the paths for Qt, so CMake knows where it is
set(QT_PATH "C:/Qt")
set(QT_ENV_PATH "${QT_PATH}/6.8.1/msvc2022_64")

# Displays the paths we have just set in console (if in verbose)
message(Verbose "QT Path: ${QT_PATH}")
message(Verbose "QT Env : ${QT_ENV_PATH}")

# Add a prefix path for the correct Qt install
set(CMAKE_PREFIX_PATH ${QT_ENV_PATH})

# Set all CMake Qt auto flags to true
set(CMAKE_AUTOMOC ON)

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
)

# Store all of the packages source files in a variable and assign these to there own source_group
set(BREACHED_TS_SRC
    ${CMAKE_CURRENT_LIST_DIR}/src/breached-plugin.h
    ${CMAKE_CURRENT_LIST_DIR}/src/breached-plugin.cpp
)
source_group("Breached Teamspeak" FILES ${BREACHED_TS_SRC})

#----------------------------------------------------------------------------------------------------------------------#