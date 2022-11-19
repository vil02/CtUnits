#define BOOST_TEST_MODULE TestTypeConversionUtils

#include "../CtUnits/ctu/TypeConversionUtils.hpp"
#include "../CtUnits/ctu/UdMap.hpp"
#include <boost/static_assert.hpp>
#include <boost/test/included/unit_test.hpp>
#include <type_traits>

BOOST_AUTO_TEST_CASE(TestUnitDimensionToUdPair)
{
    using input = ctu::UnitDimension<int, 3>;
    using expected_output = ctu::tcu::UdPair<int, ctu::tcu::Dim<3>>;
    using actual = ctu::tcu::UnitDimensionToUdPair<input>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected_output>);
}

BOOST_AUTO_TEST_CASE(TestUdPairToUnitDimension)
{
    using input = ctu::tcu::UdPair<char, ctu::tcu::Dim<10>>;
    using expected_output = ctu::UnitDimension<char, 10>;
    using actual = ctu::tcu::UdPairToUnitDimension<input>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected_output>);
}

BOOST_AUTO_TEST_CASE(TestUdMapToMpList)
{
    using input = ctu::UdMap<
        ctu::UnitDimension<int, 1>, ctu::UnitDimension<bool, 20>,
        ctu::UnitDimension<char, 3>>;
    using expected_output = ctu::UdMap<
        ctu::tcu::UdPair<int, ctu::tcu::Dim<1>>,
        ctu::tcu::UdPair<bool, ctu::tcu::Dim<20>>,
        ctu::tcu::UdPair<char, ctu::tcu::Dim<3>>>;
    using actual = ctu::tcu::UdMapToMpList<input>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected_output>);
}

BOOST_AUTO_TEST_CASE(TestMpListToUdMap)
{
    using input = ctu::UdMap<
        ctu::tcu::UdPair<bool, ctu::tcu::Dim<10>>,
        ctu::tcu::UdPair<double, ctu::tcu::Dim<-20>>,
        ctu::tcu::UdPair<char, ctu::tcu::Dim<-300>>>;
    using expected_output = ctu::UdMap<
        ctu::UnitDimension<bool, 10>, ctu::UnitDimension<double, -20>,
        ctu::UnitDimension<char, -300>>;
    using actual = ctu::tcu::MpListToUdMap<input>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected_output>);
}
