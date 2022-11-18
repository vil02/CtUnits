#define BOOST_TEST_MODULE TestTypeConversionUtils

#include "../CtUnits/ctu/TypeConversionUtils.hpp"
#include "../CtUnits/ctu/ud_list.hpp"
#include <boost/test/included/unit_test.hpp>
#include <boost/static_assert.hpp>
#include <type_traits>

BOOST_AUTO_TEST_CASE(test_unit_dimension_to_ud_pair)
{
    using input = ctu::UnitDimension<int, 3>;
    using expected_output = ctu::tcu::ud_pair<int, ctu::tcu::dim_t<3> >;
    using actual = ctu::tcu::unit_dimension_to_ud_pair<input>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected_output>);
}

BOOST_AUTO_TEST_CASE(test_ud_pair_to_unit_dimension)
{
    using input = ctu::tcu::ud_pair<char, ctu::tcu::dim_t<10> >;
    using expected_output = ctu::UnitDimension<char, 10>;
    using actual = ctu::tcu::ud_pair_to_unit_dimension<input>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected_output>);
}

BOOST_AUTO_TEST_CASE(test_units_dimensions_to_mp_list)
{
    using input = ctu::ud_list<
        ctu::UnitDimension<int, 1>,
        ctu::UnitDimension<bool, 20>,
        ctu::UnitDimension<char, 3> >;
    using expected_output = ctu::ud_list<
        ctu::tcu::ud_pair<int, ctu::tcu::dim_t<1> >,
        ctu::tcu::ud_pair<bool, ctu::tcu::dim_t<20> >,
        ctu::tcu::ud_pair<char, ctu::tcu::dim_t<3> > >;
    using actual = ctu::tcu::units_dimensions_to_mp_list<input>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected_output>);
  }

BOOST_AUTO_TEST_CASE(test_mp_list_to_units_dimensions)
{
  using input = ctu::ud_list<
      ctu::tcu::ud_pair<bool, ctu::tcu::dim_t<10> >,
      ctu::tcu::ud_pair<double, ctu::tcu::dim_t<-20> >,
      ctu::tcu::ud_pair<char, ctu::tcu::dim_t<-300> > >;
    using expected_output = ctu::ud_list<
        ctu::UnitDimension<bool, 10>,
        ctu::UnitDimension<double, -20>,
        ctu::UnitDimension<char, -300> >;
    using actual = ctu::tcu::mp_list_to_units_dimensions<input>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected_output>);
}
