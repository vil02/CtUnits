#define BOOST_TEST_MODULE TestTypeConversionUtils

#include "../CtUnits/ctu/TypeConversionUtils.hpp"
#include <boost/mp11.hpp>
#include <boost/test/included/unit_test.hpp>
#include <boost/static_assert.hpp>
#include <type_traits>

BOOST_AUTO_TEST_CASE(test_unit_dimension_to_mp_list)
{
    using input = ctu::UnitDimension<int, 3>;
    using expected_output = boost::mp11::mp_list<int, boost::mp11::mp_int<3> >;
    using actual = ctu::tcu::unit_dimension_to_mp_list<input>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected_output>);
}

BOOST_AUTO_TEST_CASE(test_mp_list_to_unit_dimension)
{
    using input = boost::mp11::mp_list<char, boost::mp11::mp_int<10> >;
    using expected_output = ctu::UnitDimension<char, 10>;
    using actual = ctu::tcu::mp_list_to_unit_dimension<input>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected_output>);
}

BOOST_AUTO_TEST_CASE(test_units_dimensions_to_mp_list)
{
    using input = boost::mp11::mp_list<
        ctu::UnitDimension<int, 1>,
        ctu::UnitDimension<bool, 20>,
        ctu::UnitDimension<char, 3> >;
    using expected_output = boost::mp11::mp_list<
        boost::mp11::mp_list<int, boost::mp11::mp_int<1> >,
        boost::mp11::mp_list<bool, boost::mp11::mp_int<20> >,
        boost::mp11::mp_list<char, boost::mp11::mp_int<3> > >;
    using actual = ctu::tcu::units_dimensions_to_mp_list<input>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected_output>);
  }

BOOST_AUTO_TEST_CASE(test_mp_list_to_units_dimensions)
{
  using input = boost::mp11::mp_list<
      boost::mp11::mp_list<bool, boost::mp11::mp_int<10> >,
      boost::mp11::mp_list<double, boost::mp11::mp_int<-20> >,
      boost::mp11::mp_list<char, boost::mp11::mp_int<-300> > >;
    using expected_output = boost::mp11::mp_list<
        ctu::UnitDimension<bool, 10>,
        ctu::UnitDimension<double, -20>,
        ctu::UnitDimension<char, -300> >;
    using actual = ctu::tcu::mp_list_to_units_dimensions<input>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected_output>);
}
