#define BOOST_TEST_MODULE TestTypeConversionUtils

#include "../CtUnits/ctu/TypeConversionUtils.hpp"
#include "../CtUnits/ctu/UdMap.hpp"
#include <boost/mp11.hpp>
#include <boost/static_assert.hpp>
#include <boost/test/included/unit_test.hpp>
#include <type_traits>

BOOST_AUTO_TEST_CASE(TestUnitDimensionToUdPair)
{
    using input = ctu::UnitDimension<int, 3, 8>;
    using expected_output = ctu::tcu::UdPair<int, ctu::Dimension<3, 8>>;
    using actual = ctu::tcu::UnitDimensionToUdPair<input>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected_output>);
}

BOOST_AUTO_TEST_CASE(TestUdPairToUnitDimension)
{
    using input = ctu::tcu::UdPair<char, ctu::Dimension<10>>;
    using expected_output = ctu::UnitDimension<char, 10>;
    using actual = ctu::tcu::UdPairToUnitDimension<input>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected_output>);
}

BOOST_AUTO_TEST_CASE(TestUdMapToMpList)
{
    using input = ctu::UdMap<
        ctu::UnitDimension<bool, 20>, ctu::UnitDimension<char, 3>,
        ctu::UnitDimension<int, 1>>;
    using expected_output = boost::mp11::mp_list<
        ctu::tcu::UdPair<bool, ctu::Dimension<20>>,
        ctu::tcu::UdPair<char, ctu::Dimension<3>>,
        ctu::tcu::UdPair<int, ctu::Dimension<1>>>;
    using actual = ctu::tcu::UdMapToMpList<input>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected_output>);
}

BOOST_AUTO_TEST_CASE(TestMpListToUdMap)
{
    using input = boost::mp11::mp_list<
        ctu::tcu::UdPair<bool, ctu::Dimension<10>>,
        ctu::tcu::UdPair<char, ctu::Dimension<-300>>,
        ctu::tcu::UdPair<double, ctu::Dimension<-20>>>;
    using expected_output = ctu::UdMap<
        ctu::UnitDimension<bool, 10>, ctu::UnitDimension<char, -300>,
        ctu::UnitDimension<double, -20>>;
    using actual = ctu::tcu::MpListToUdMap<input>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected_output>);
}
