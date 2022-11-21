set(example_name speed_units)

add_regular_executable(${example_name}.cpp)

add_test(NAME test_output_${example_name} COMMAND ${example_name})
set_tests_properties(
    test_output_${example_name}
    PROPERTIES PASS_REGULAR_EXPRESSION
    "140 km/h is 38.8889 m/s")
