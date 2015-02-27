###################################
#
# Configuration des tests unitaires
#
###################################


include( CTest )
enable_testing()

# Memory checking
find_program( CTEST_MEMORYCHECK_COMMAND valgrind )
set( CTEST_MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full" )


## CppUnit
find_library( CPPUNIT cppunit)
if( CPPUNIT-NOTFOUND )
  message( FATAL_ERROR "cppunit est introuvable" )
endif(CPPUNIT-NOTFOUND )
##


## macro to add test target
add_custom_target( check )

function( make_test rep )
    file( GLOB_RECURSE source_files ${rep}/*.cpp )
    add_subdirectory( ${rep} )
    add_executable(arccos_${rep}_tests  ${source_files} )
    add_test( ${rep} arccos_${rep}_tests )
    target_link_libraries(arccos_${rep}_tests cppunit)
    #add_dependencies( arccos_${rep}_tests libarccos )
    add_dependencies( check arccos_${rep}_tests )
endfunction(make_test)

##


## Options de compilation
## Obligatoire, active le standard c++11 (ou 14)
add_definitions("-std=c++14")

## messages du compilateur
add_definitions("-Wall")
add_definitions("-Wextra")

# TODO: paramétrer avec une variable d'environnement
add_definitions( "-DLOGLEVEL=2")

# Ajout de chaque répertoire de test
add_subdirectory( "mptoolstests" )
add_subdirectory( "structstests" )
# -------------------------

