set(printed_output "123 meters is 4842.52 inches")

set(example_name meters_and_inches)

add_regular_executable(${example_name}.cpp)

add_test(NAME test_output_${example_name} COMMAND ${example_name})
set_tests_properties(
    test_output_${example_name}
    PROPERTIES PASS_REGULAR_EXPRESSION
    ${printed_output})

set(example_name_simple meters_and_inches_simple)

add_regular_executable(${example_name_simple}.cpp)

add_test(NAME test_output_${example_name_simple} COMMAND ${example_name_simple})
set_tests_properties(
    test_output_${example_name_simple}
    PROPERTIES PASS_REGULAR_EXPRESSION
    ${printed_output})
