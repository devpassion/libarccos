file( GLOB_RECURSE tpl_cpp *.cpp )


add_library( libarccos_impl ${tpl_cpp} )
target_link_libraries( libarccos_impl libarccos    )