##########################################
#
# Configuration générale de la compilation
#
##########################################

cmake_minimum_required(VERSION 2.6)

project(libarccos)

# Pas d'éxecutable
# add_executable(libarccos )
# install(TARGETS libarccos RUNTIME DESTINATION bin)

include_directories( include tpl )

add_subdirectory(include)


## Tests unitaires
add_subdirectory( tests )
add_subdirectory( tpl )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)

# -------------------------
