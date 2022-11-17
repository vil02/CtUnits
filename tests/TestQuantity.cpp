#define BOOST_TEST_MODULE TestQuantity

#include "../CtUnits/ctu/Quantity.hpp"
#include <boost/mp11.hpp>
#include <boost/test/included/unit_test.hpp>
#include <boost/static_assert.hpp>
#include <type_traits>
#include <cstdint>

BOOST_AUTO_TEST_CASE(test_get_value)
{
    const int some_value = 10;
    using quantity_type = ctu::Quantity<
        std::remove_const_t<decltype(some_value)>,
        boost::mp11::mp_list<
            ctu::UnitDimension<bool, 1>,
            ctu::UnitDimension<char, -3> > >;
    const auto example_quantity = quantity_type(some_value);
    BOOST_CHECK_EQUAL(example_quantity.get_value(), some_value);
}

BOOST_AUTO_TEST_CASE(test_add)
{
    using value_type = unsigned;
    const value_type value_a = 10;
    const value_type value_b = 10;
    using quantity_type = ctu::Quantity<
        value_type,
        boost::mp11::mp_list<
            ctu::UnitDimension<char, -4>,
            ctu::UnitDimension<int, 4> > >;
    const auto quantity_a = quantity_type(value_a);
    const auto quantity_b = quantity_type(value_b);
    const auto result = quantity_a+quantity_b;
    BOOST_STATIC_ASSERT(
        std::is_same_v<std::remove_const_t<decltype(result)>,
        quantity_type>);
    BOOST_CHECK_EQUAL(result.get_value(), value_a+value_b);
}

BOOST_AUTO_TEST_CASE(test_substract)
{
    using value_type = int;
    const value_type value_a = 4;
    const value_type value_b = -5;
    using quantity_type = ctu::Quantity<
        value_type,
        boost::mp11::mp_list<
            ctu::UnitDimension<bool, -2>,
            ctu::UnitDimension<long double, 3> > >;
    const auto quantity_a = quantity_type(value_a);
    const auto quantity_b = quantity_type(value_b);
    const auto result = quantity_a-quantity_b;
    BOOST_STATIC_ASSERT(
        std::is_same_v<std::remove_const_t<decltype(result)>,
        quantity_type>);
    BOOST_CHECK_EQUAL(result.get_value(), value_a-value_b);
}

BOOST_AUTO_TEST_CASE(test_multiply)
{
    using value_type = int;
    const value_type value_a = 4;
    using quantity_type_a = ctu::Quantity<
        value_type,
        boost::mp11::mp_list<
            ctu::UnitDimension<bool, -2>,
            ctu::UnitDimension<char, 4>,
            ctu::UnitDimension<long double, 3> > >;
    const auto quantity_a = quantity_type_a(value_a);

    const value_type value_b = 3;
    using quantity_type_b = ctu::Quantity<
        value_type,
        boost::mp11::mp_list<
            ctu::UnitDimension<bool, 3>,
            ctu::UnitDimension<char, -4>,
            ctu::UnitDimension<double, 1>,
            ctu::UnitDimension<int, 10>,
            ctu::UnitDimension<long double, 2> > >;
    const auto quantity_b = quantity_type_b(value_b);

    using expected_result_type = ctu::Quantity<
        value_type,
        boost::mp11::mp_list<
            ctu::UnitDimension<bool, 1>,
            ctu::UnitDimension<double, 1>,
            ctu::UnitDimension<int, 10>,
            ctu::UnitDimension<long double, 5> > >;
    const auto result = quantity_a*quantity_b;
    BOOST_STATIC_ASSERT(
        std::is_same_v<std::remove_const_t<decltype(result)>,
        expected_result_type>);
    BOOST_CHECK_EQUAL(result.get_value(), value_a*value_b);
}

BOOST_AUTO_TEST_CASE(test_divide)
{
    using value_type = int;
    const value_type value_a = 12;
    using quantity_type_a = ctu::Quantity<
        value_type,
        boost::mp11::mp_list<
            ctu::UnitDimension<bool, -2>,
            ctu::UnitDimension<char, 4>,
            ctu::UnitDimension<long double, 3> > >;
    const auto quantity_a = quantity_type_a(value_a);

    const value_type value_b = 3;
    using quantity_type_b = ctu::Quantity<
        value_type,
        boost::mp11::mp_list<
            ctu::UnitDimension<bool, 3>,
            ctu::UnitDimension<char, -4>,
            ctu::UnitDimension<double, 1>,
            ctu::UnitDimension<int, 10>,
            ctu::UnitDimension<long double, 3> > >;
    const auto quantity_b = quantity_type_b(value_b);

    using expected_result_type = ctu::Quantity<
        value_type,
        boost::mp11::mp_list<
            ctu::UnitDimension<bool, -5>,
            ctu::UnitDimension<char, 8>,
            ctu::UnitDimension<double, -1>,
            ctu::UnitDimension<int, -10> > >;
    const auto result = quantity_a/quantity_b;
    BOOST_STATIC_ASSERT(
        std::is_same_v<std::remove_const_t<decltype(result)>,
        expected_result_type>);
    BOOST_CHECK_EQUAL(result.get_value(), value_a/value_b);
}

using value_types = boost::mp11::mp_list<std::int8_t, std::int16_t, std::int32_t, std::int64_t>;

BOOST_AUTO_TEST_CASE_TEMPLATE(has_same_size_as_value_type, value_type, value_types)
{
      using units_dimensions = boost::mp11::mp_list<
          ctu::UnitDimension<bool, -1>,
          ctu::UnitDimension<char, 2>,
          ctu::UnitDimension<double, 3>,
          ctu::UnitDimension<int, -23> >;
      BOOST_STATIC_ASSERT(
          sizeof(ctu::Quantity<value_type, units_dimensions>) == sizeof(value_type));
}
