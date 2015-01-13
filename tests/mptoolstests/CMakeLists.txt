# # 
# 
# # 

make_test( "intervaltests" )
make_test( "loggingtests" )
make_test( "typelisttests" )

# Déplacer
add_definitions( "-DTMP=build/tmp" )