##########################################
#
# Configuration générale de la compilation
#
##########################################

cmake_minimum_required(VERSION 2.6)

project(libarccos)

# add_executable(libarccos)

# install(TARGETS libarccos RUNTIME DESTINATION bin)

add_subdirectory(src)


## Tests unitaires
include( CTest )
enable_testing()
add_subdirectory( tests )

# -------------------------
