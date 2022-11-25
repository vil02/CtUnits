#define BOOST_TEST_MODULE TestQuantityPow

#include "../CtUnits/ctu/Quantity.hpp"
#include <boost/mp11.hpp>
#include <boost/static_assert.hpp>
#include <boost/test/included/unit_test.hpp>
#include <ratio>
#include <type_traits>

using ExampleUnitDim = ctu::UdMap<
    ctu::UnitDimension<bool, 1>, ctu::UnitDimension<char, -3>,
    ctu::UnitDimension<int, 5>>;

const auto example_quantity = ctu::Quantity<long double, ExampleUnitDim>(4.0L);

BOOST_AUTO_TEST_CASE(TestPowWithNaturalPower)
{
    const auto expected = ctu::Quantity<
        long double,
        ctu::UdMap<
            ctu::UnitDimension<bool, 2>, ctu::UnitDimension<char, -6>,
            ctu::UnitDimension<int, 10>>>(16.0L);
    const auto actual = example_quantity.pow<std::ratio<2>>();
    static_assert(std::is_same_v<decltype(actual), decltype(expected)>);
    BOOST_TEST(actual.get_value() == expected.get_value());
}

BOOST_AUTO_TEST_CASE(TestPowWithFractionalPower)
{
    const auto expected = ctu::Quantity<
        long double,
        ctu::UdMap<
            ctu::UnitDimension<bool, 1, 2>, ctu::UnitDimension<char, -3, 2>,
            ctu::UnitDimension<int, 5, 2>>>(2.0L);
    const auto actual = example_quantity.pow<std::ratio<1, 2>>();
    static_assert(std::is_same_v<decltype(actual), decltype(expected)>);
    BOOST_TEST(actual.get_value() == expected.get_value());
}

BOOST_AUTO_TEST_CASE(TestPowWithZeroPower)
{
    const auto expected = ctu::Quantity<long double, ctu::UdMap<>>(1.0L);
    const auto actual = example_quantity.pow<std::ratio<0>>();
    static_assert(std::is_same_v<decltype(actual), decltype(expected)>);
    BOOST_TEST(actual.get_value() == expected.get_value());
}
