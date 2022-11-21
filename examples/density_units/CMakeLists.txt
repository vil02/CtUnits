set(printed_output "1000 kg/m\\^3 is 62.4279 lbs/ft\\^3")

set(example_name density_units)

add_regular_executable(${example_name}.cpp)

add_test(NAME test_output_${example_name} COMMAND ${example_name} 1000)
set_tests_properties(
    test_output_${example_name}
    PROPERTIES PASS_REGULAR_EXPRESSION
    ${printed_output})

set(example_name_simple density_units_simple)

add_regular_executable(${example_name_simple}.cpp)

add_test(
    NAME test_output_${example_name_simple}
    COMMAND ${example_name_simple} 1000)
set_tests_properties(
    test_output_${example_name_simple}
    PROPERTIES PASS_REGULAR_EXPRESSION
    ${printed_output})
