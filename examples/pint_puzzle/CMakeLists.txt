set(example_name pint_puzzle)

add_regular_executable(${example_name}.cpp)

add_test(NAME test_output_${example_name} COMMAND ${example_name})
set_tests_properties(
    test_output_${example_name}
    PROPERTIES PASS_REGULAR_EXPRESSION
    "A cube with side length of 3.26099 inches has a volume of one pint.")
