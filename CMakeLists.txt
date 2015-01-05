##########################################
#
# Configuration générale de la compilation
#
##########################################

cmake_minimum_required(VERSION 2.6)

project(libarccos)


# Pad d'éxecutable
# add_executable(libarccos)
# install(TARGETS libarccos RUNTIME DESTINATION bin)

add_subdirectory(src)


## Tests unitaires
add_subdirectory( tests )

# -------------------------
