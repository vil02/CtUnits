function(add_regular_test test_source)
    get_filename_component(core_name ${test_source} NAME_WLE)
    add_executable(${core_name} ${test_source})
    target_link_libraries(${core_name}
        PRIVATE
            project_options
            project_warnings)

    add_test(Run_${core_name} ${core_name})
endfunction()

file(GLOB test_sources *.cpp)
foreach (test_source ${test_sources})
    add_regular_test(${test_source})
endforeach()
