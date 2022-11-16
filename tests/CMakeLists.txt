function(add_regular_test core_name)
    add_executable(${core_name} ${core_name}.cpp)
    target_link_libraries(${core_name}
        PRIVATE
            project_options
            project_warnings)

    add_test(Run_${core_name} ${core_name})
endfunction()

add_regular_test(TestQuantity)
add_regular_test(TestTypeConversionUtils)
