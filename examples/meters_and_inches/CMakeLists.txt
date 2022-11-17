set(example_name meters_and_inches)

add_executable(${example_name} ${example_name}.cpp)
target_link_libraries(${example_name}
    PRIVATE
        project_options
        project_warnings)

add_test(NAME test_output_${example_name} COMMAND ${example_name})
set_tests_properties(
    test_output_${example_name}
    PROPERTIES PASS_REGULAR_EXPRESSION
    "123 meters is 4842.52 inches")
