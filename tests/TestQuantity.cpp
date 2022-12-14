#define BOOST_TEST_MODULE TestQuantity

#include "../CtUnits/ctu/Quantity.hpp"
#include <boost/mp11.hpp>
#include <boost/static_assert.hpp>
#include <boost/test/included/unit_test.hpp>
#include <cstdint>
#include <type_traits>

using ExampleUnitDimA =
    ctu::UdMap<ctu::UnitDimension<bool, 1>, ctu::UnitDimension<char, -3>>;
using ExampleUnitDimB =
    ctu::UdMap<ctu::UnitDimension<char, -4>, ctu::UnitDimension<int, 4>>;
using ExampleUnitDimC = ctu::UdMap<
    ctu::UnitDimension<bool, -2>, ctu::UnitDimension<long double, 3>>;
using ExampleUnitDimD = ctu::UdMap<ctu::UnitDimension<bool, 1>>;
using ExampleUnitDimE = ctu::UdMap<>;

using UnitDimExamples = boost::mp11::mp_list<
    ExampleUnitDimA, ExampleUnitDimB, ExampleUnitDimC, ExampleUnitDimD,
    ExampleUnitDimE>;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_get_value, UnitDimExample, UnitDimExamples)
{
    const int some_value = 10;
    using quantity_type = ctu::Quantity<
        std::remove_const_t<decltype(some_value)>, UnitDimExample>;
    const auto example_quantity = quantity_type(some_value);
    BOOST_CHECK_EQUAL(example_quantity.get_value(), some_value);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(
    test_plus_asssign, UnitDimExample, UnitDimExamples)
{
    using value_type = unsigned;
    const value_type some_value = 11;
    const value_type some_diff = 12;

    value_type some_value_copy = some_value;

    using quantity_type = ctu::Quantity<value_type, UnitDimExample>;
    auto quantity = quantity_type(some_value);
    quantity += quantity_type(some_diff);
    BOOST_CHECK_EQUAL(quantity.get_value(), some_value_copy += some_diff);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_add, UnitDimExample, UnitDimExamples)
{
    using value_type = unsigned;
    const value_type value_a = 10;
    const value_type value_b = 10;
    using quantity_type = ctu::Quantity<value_type, UnitDimExample>;
    const auto quantity_a = quantity_type(value_a);
    const auto quantity_b = quantity_type(value_b);
    const auto result = quantity_a + quantity_b;
    BOOST_STATIC_ASSERT(
        std::is_same_v<std::remove_const_t<decltype(result)>, quantity_type>);
    BOOST_CHECK_EQUAL(result.get_value(), value_a + value_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(
    test_substract_asssign, UnitDimExample, UnitDimExamples)
{
    using value_type = int;
    const value_type some_value = 100;
    const value_type some_diff = 90;

    value_type some_value_copy = some_value;

    using quantity_type = ctu::Quantity<value_type, UnitDimExample>;
    auto quantity = quantity_type(some_value);
    quantity -= quantity_type(some_diff);
    BOOST_CHECK_EQUAL(quantity.get_value(), some_value_copy -= some_diff);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_substract, UnitDimExample, UnitDimExamples)
{
    using value_type = int;
    const value_type value_a = 4;
    const value_type value_b = -5;
    using quantity_type = ctu::Quantity<value_type, UnitDimExample>;
    const auto quantity_a = quantity_type(value_a);
    const auto quantity_b = quantity_type(value_b);
    const auto result = quantity_a - quantity_b;
    BOOST_STATIC_ASSERT(
        std::is_same_v<std::remove_const_t<decltype(result)>, quantity_type>);
    BOOST_CHECK_EQUAL(result.get_value(), value_a - value_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_unary_minus, UnitDimExample, UnitDimExamples)
{
    using value_type = int;
    const value_type some_value = 100;

    using quantity_type = ctu::Quantity<value_type, UnitDimExample>;
    const auto quantity = quantity_type(some_value);
    BOOST_STATIC_ASSERT(
        std::is_same_v<
            std::remove_const_t<decltype(quantity)>, decltype(-quantity)>);
    BOOST_CHECK_EQUAL(-quantity.get_value(), (-quantity).get_value());
}

template <typename ValueType>
using DimensionlessQuantity = ctu::Quantity<ValueType, ctu::UdMap<>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(
    test_multiply_assign, UnitDimExample, UnitDimExamples)
{
    using value_type = int;
    const value_type some_value = 3;
    value_type some_value_copy = some_value;
    const value_type example_factor = 10;
    auto quantity = ctu::Quantity<value_type, UnitDimExample>(some_value);
    quantity *= DimensionlessQuantity<value_type>(example_factor);
    BOOST_CHECK_EQUAL(quantity.get_value(), some_value_copy *= example_factor);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(
    test_divide_assign, UnitDimExample, UnitDimExamples)
{
    using value_type = unsigned;
    const value_type some_value = 300;
    value_type some_value_copy = some_value;
    const value_type example_factor = 100;
    auto quantity = ctu::Quantity<value_type, UnitDimExample>(some_value);
    quantity /= DimensionlessQuantity<value_type>(example_factor);
    BOOST_CHECK_EQUAL(quantity.get_value(), some_value_copy /= example_factor);
}

struct ExampleUnitsDimsA
{
    using units_dims_a = ctu::UdMap<
        ctu::UnitDimension<bool, -2>, ctu::UnitDimension<char, 4>,
        ctu::UnitDimension<long double, 3>>;

    using units_dims_b = ctu::UdMap<
        ctu::UnitDimension<bool, 3>, ctu::UnitDimension<char, -4>,
        ctu::UnitDimension<double, 1>, ctu::UnitDimension<int, 10>,
        ctu::UnitDimension<long double, 3>>;

    using prod_units_dims = ctu::UdMap<
        ctu::UnitDimension<bool, 1>, ctu::UnitDimension<double, 1>,
        ctu::UnitDimension<int, 10>, ctu::UnitDimension<long double, 6>>;

    using div_units_dims = ctu::UdMap<
        ctu::UnitDimension<bool, -5>, ctu::UnitDimension<char, 8>,
        ctu::UnitDimension<double, -1>, ctu::UnitDimension<int, -10>>;
};

struct ExampleUnitsDimsB
{
    using units_dims_a = ctu::UdMap<
        ctu::UnitDimension<bool, 1>, ctu::UnitDimension<long double, -2>>;

    using units_dims_b =
        ctu::UdMap<ctu::UnitDimension<char, 3>, ctu::UnitDimension<int, -4>>;

    using prod_units_dims = ctu::UdMap<
        ctu::UnitDimension<bool, 1>, ctu::UnitDimension<char, 3>,
        ctu::UnitDimension<int, -4>, ctu::UnitDimension<long double, -2>>;

    using div_units_dims = ctu::UdMap<
        ctu::UnitDimension<bool, 1>, ctu::UnitDimension<char, -3>,
        ctu::UnitDimension<int, 4>, ctu::UnitDimension<long double, -2>>;
};

struct ExampleUnitsDimsC
{
    using units_dims_a = ctu::UdMap<>;
    using units_dims_b = units_dims_a;
    using prod_units_dims = units_dims_a;
    using div_units_dims = units_dims_a;
};

struct ExampleUnitsDimsD
{
    using units_dims_a = ctu::UdMap<>;
    using units_dims_b = ctu::UdMap<ctu::UnitDimension<int, -5>>;
    using prod_units_dims = units_dims_b;
    using div_units_dims = ctu::UdMap<ctu::UnitDimension<int, 5>>;
};

struct ExampleUnitsDimsE
{
    using units_dims_a = ctu::UdMap<ctu::UnitDimension<char, 2>>;
    using units_dims_b = ctu::UdMap<>;
    using prod_units_dims = units_dims_a;
    using div_units_dims = units_dims_a;
};

using UnitsDimsExamples = boost::mp11::mp_list<
    ExampleUnitsDimsA, ExampleUnitsDimsB, ExampleUnitsDimsC, ExampleUnitsDimsD,
    ExampleUnitsDimsE>;

BOOST_AUTO_TEST_CASE_TEMPLATE(
    test_multiply, UnitsDimsExample, UnitsDimsExamples)
{
    using value_type = int;
    const value_type value_a = 4;
    using quantity_type_a =
        ctu::Quantity<value_type, typename UnitsDimsExample::units_dims_a>;
    const auto quantity_a = quantity_type_a(value_a);

    const value_type value_b = 3;
    using quantity_type_b =
        ctu::Quantity<value_type, typename UnitsDimsExample::units_dims_b>;
    const auto quantity_b = quantity_type_b(value_b);

    using expected_result_type =
        ctu::Quantity<value_type, typename UnitsDimsExample::prod_units_dims>;
    const auto result = quantity_a * quantity_b;
    BOOST_STATIC_ASSERT(
        std::is_same_v<
            std::remove_const_t<decltype(result)>, expected_result_type>);
    BOOST_STATIC_ASSERT(
        std::is_same_v<
            decltype(quantity_b * quantity_a), expected_result_type>);
    BOOST_CHECK_EQUAL(result.get_value(), value_a * value_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_divide, UnitsDimsExample, UnitsDimsExamples)
{
    using value_type = int;
    const value_type value_a = 12;
    using quantity_type_a =
        ctu::Quantity<value_type, typename UnitsDimsExample::units_dims_a>;
    const auto quantity_a = quantity_type_a(value_a);

    const value_type value_b = 3;
    using quantity_type_b =
        ctu::Quantity<value_type, typename UnitsDimsExample::units_dims_b>;
    const auto quantity_b = quantity_type_b(value_b);

    using expected_result_type =
        ctu::Quantity<value_type, typename UnitsDimsExample::div_units_dims>;
    const auto result = quantity_a / quantity_b;
    BOOST_STATIC_ASSERT(
        std::is_same_v<
            std::remove_const_t<decltype(result)>, expected_result_type>);
    BOOST_CHECK_EQUAL(result.get_value(), value_a / value_b);
}

using ValueTypes =
    boost::mp11::mp_list<std::int8_t, std::int16_t, std::int32_t, std::int64_t>;

BOOST_AUTO_TEST_CASE_TEMPLATE(
    has_same_size_as_value_type, ValueType, ValueTypes)
{
    using units_dimensions = ctu::UdMap<
        ctu::UnitDimension<bool, -1>, ctu::UnitDimension<char, 2>,
        ctu::UnitDimension<double, 3>, ctu::UnitDimension<int, -23>>;
    BOOST_STATIC_ASSERT(
        sizeof(ctu::Quantity<ValueType, units_dimensions>) ==
        sizeof(ValueType));
}
