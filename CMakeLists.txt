##########################################
#
# Configuration générale de la compilation
#
##########################################

cmake_minimum_required(VERSION 2.6)

project(libarccos)


# Add files for IDE
FILE (GLOB_RECURSE clion_all_headers ${CMAKE_SOURCE_DIR}/*)
ADD_CUSTOM_TARGET(all_clion
    SOURCES ${clion_all_headers}
)

include_directories( include tpl )

# Documentation
add_subdirectory( doc )

# Headers files
add_subdirectory(include)

# template implémentations
add_subdirectory( tpl )

# Tests
add_subdirectory( tests )




# -------------------------
