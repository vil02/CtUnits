#define BOOST_TEST_MODULE TestGetUnitId

#include "../CtUnits/ctu/MpUnitsDimensionsUtils.hpp"
#include "../CtUnits/ctu/UnitDimension.hpp"
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(GetUnitIdReturnsSameResultForDifferentDims)
{
    using UdPairA =
        ctu::tcu::UnitDimensionToUdPair<ctu::UnitDimension<bool, 2>>;
    using UdPairB =
        ctu::tcu::UnitDimensionToUdPair<ctu::UnitDimension<bool, 10>>;

    const auto unit_id_a = ctu::ud_operations::get_unit_id<UdPairA>();
    const auto unit_id_b = ctu::ud_operations::get_unit_id<UdPairB>();
    BOOST_CHECK_EQUAL(unit_id_a, unit_id_b);
}

BOOST_AUTO_TEST_CASE(GetUnitIdReturnsDifferentResultResultForDifferentUnits)
{
    using UdPairA =
        ctu::tcu::UnitDimensionToUdPair<ctu::UnitDimension<bool, 3>>;
    using UdPairB =
        ctu::tcu::UnitDimensionToUdPair<ctu::UnitDimension<char, 3>>;

    const auto unit_id_a = ctu::ud_operations::get_unit_id<UdPairA>();
    const auto unit_id_b = ctu::ud_operations::get_unit_id<UdPairB>();
    BOOST_CHECK(unit_id_a != unit_id_b);
}
