#----------------------------------------------------------------------------------------------------------------------#
# Build Folder Safe Guards

# TODO: Rewrite msg
# Make sure that the build or configure command hasn't been called at the root directory
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
        FATAL_ERROR
        "Builds can not be run from the src directory. You must make a build directory and run CMake from there."
    )
endif()

#----------------------------------------------------------------------------------------------------------------------#
# Build Type Safe Guards


# CMAKE_BUILD_TYPE is not used by multi-configuration generators, so we need to check it first
get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

# Default to the Debug build when the provided build type is nullish
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

#----------------------------------------------------------------------------------------------------------------------#
# Version Safe Guards

# Ensures that all source files have their extensions explicitly listed, as this is the new behavior of CMake
if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.20")
	cmake_policy(SET CMP0115 NEW)
endif()

#----------------------------------------------------------------------------------------------------------------------#