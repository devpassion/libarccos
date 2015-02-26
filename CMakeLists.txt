##########################################
#
# Configuration générale de la compilation
#
##########################################

cmake_minimum_required(VERSION 2.6)

project(libarccos)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)
#set( CMAKE_PROJECT_BINARY_DIR /home/tim288/prog/kdev/libarccos/build)

ENABLE_TESTING()
INCLUDE(CTest)

# Pas d'éxecutable
# add_executable(libarccos )
# install(TARGETS libarccos RUNTIME DESTINATION bin)

add_custom_target( check )

include_directories( include tpl )

add_subdirectory( doc )

add_subdirectory(include)


add_subdirectory( tests )

add_subdirectory( tpl )


# -------------------------
