# # 
# 
# # 

make_test( "intervaltests" )
make_test( "loggingtests" )
make_test( "typelisttests" )
make_test( "typetraitstests" )

# Déplacer
add_definitions( "-DTMP=build/tmp" )