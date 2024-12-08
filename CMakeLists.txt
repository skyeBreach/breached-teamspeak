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
# Project Metadata

# Read the config metadata JSON file
file(READ ${CMAKE_CURRENT_SOURCE_DIR}/config/plugin.json PluginConfigData)

# Define the projects information metadata from the provided metadata.json config 
string(JSON PROJECT_NAME            GET ${PluginConfigData} name        )
string(JSON PROJECT_LABEL           GET ${PluginConfigData} label       )
string(JSON PROJECT_VERSION         GET ${PluginConfigData} version     )
string(JSON PROJECT_DESCRIPTION     GET ${PluginConfigData} description )
string(JSON PROJECT_HOMEPAGE_URL    GET ${PluginConfigData} homepage    )

# Initialize the project information based off of the metadata
project(
	${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
    HOMEPAGE_URL ${PROJECT_HOMEPAGE_URL}
    DESCRIPTION ${PROJECT_DESCRIPTION}
	LANGUAGES CXX
)

#----------------------------------------------------------------------------------------------------------------------#
# C++ Build Info

# Define the projects build type and environment based on what the CMake build type
if(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(PROJECT_BUILD_TYPE  "RelWithDebInfo")
    set(PROJECT_BUILD_ENV   "Production")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(PROJECT_BUILD_TYPE  "Release")
    set(PROJECT_BUILD_ENV   "Production")
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(PROJECT_BUILD_TYPE  "MinSizeRel")
    set(PROJECT_BUILD_ENV   "Production")
else()
    set(PROJECT_BUILD_TYPE  "Debug")
    set(PROJECT_BUILD_ENV   "Development")
endif()

# Warn when we are in a Debug or Development environment
if(${PROJECT_BUILD_TYPE} STREQUAL "Debug" OR ${PROJECT_BUILD_ENV} STREQUAL "Development")
    message(
        VERBOSE
            "Currently in a 'Debug' or 'Development' build, this package/library must not be released in this state!${}"
    )
endif()

# Display the current build configuration
message(STATUS "Build Type: ${PROJECT_BUILD_TYPE}")
message(STATUS "Build Env : ${PROJECT_BUILD_ENV}")

# Define the projects build metadata
string(TIMESTAMP PROJECT_BUILD_DATE "%Y-%m-%d")

# Create a build header and populate it with the current build information (e.g. version, date, environment, and config)
configure_file(
    ${CMAKE_SOURCE_DIR}/src/build.h
    ${CMAKE_CURRENT_BINARY_DIR}/src/build.h
    @ONLY
)

#----------------------------------------------------------------------------------------------------------------------#
# Qt UI Library 

# Defines the paths for Qt, so CMake knows where it is
set(QT_PATH "C:/Qt")
set(QT_ENV_PATH "${QT_PATH}/6.8.0/mingw_64")

# Displays the paths we have just set in console (if in verbose)
message(VERBOSE "QT Path: ${QT_PATH}")
message(VERBOSE "QT Env: ${QT_ENV_PATH}")

# Add a prefix path for the correct Qt install
set(CMAKE_PREFIX_PATH ${QT_ENV_PATH})

# Set all CMake Qt auto flags to true
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find an load the Qt libraries
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
link_libraries(Qt6::Core Qt6::Widgets)

#----------------------------------------------------------------------------------------------------------------------#
# Package Directories

# Assign include directories
include_directories(
    "libs/ts3client-pluginsdk/include"
)

# Store all of the packages source files in a variable and assign these to there own source_group
set(BREACHED_TS_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/src/build.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/plugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/plugin.cpp
)
source_group("BREACHED_TS_SRC" FILES ${BREACHED_TS_SRC})

#----------------------------------------------------------------------------------------------------------------------#
# Global Properties

# Enables the ability to create folders to organize projects for the .vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#----------------------------------------------------------------------------------------------------------------------#
# Project Library Definition and Properties

# Add main project "Shared" library that will be exported by this package
add_library(${PROJECT_NAME} SHARED
    ${BREACHED_TS_SRC}
)

# Enforce the use of the correct C standards
set_target_properties(${PROJECT_NAME} PROPERTIES
    CMAKE_C_STANDARD 99
    C_STANDARD_REQUIRED on
    #CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -Wall -fPIC"
)

# Enforce the use of the correct CXX standards
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Ensure that CMake outputs its compiler commands when generating
set_target_properties(${PROJECT_NAME} PROPERTIES
    CMAKE_EXPORT_COMPILE_COMMANDS ON
)

# MSVC compiler options
if ((MSVC) AND (MSVC_VERSION GREATER_EQUAL 1914))
    target_compile_options(${PROJECT_NAME} PUBLIC
        "/Zc:__cplusplus"
        "/permissive-"
    )
endif()

#----------------------------------------------------------------------------------------------------------------------#
