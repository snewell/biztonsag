add_custom_target(examples)

function(create_example name)
    add_executable(${name} EXCLUDE_FROM_ALL ${ARGN})
    target_link_libraries(${name}
        biztonsag
    )
    set_target_properties(${name} PROPERTIES
        CXX_EXTENSIONS OFF
    )
    add_dependencies(examples ${name})
endfunction()

create_example(temp temp.cpp)
