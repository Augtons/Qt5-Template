function(list_add_prefix OUTPUT_LIST PREFIX)
    foreach (item IN ITEMS ${ARGN})
        list(APPEND RET "${PREFIX}${item}")
    endforeach()
    set(${OUTPUT_LIST} ${RET} PARENT_SCOPE)
endfunction()