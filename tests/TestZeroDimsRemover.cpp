#define BOOST_TEST_MODULE TestZeroDimsRemover

#include "../CtUnits/ctu/MpUnitsDimensionsUtils.hpp"
#include "../CtUnits/ctu/UnitDimension.hpp"
#include <boost/mp11.hpp>
#include <boost/static_assert.hpp>
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(TestZeroDimsRemover)
{
    using input = boost::mp11::mp_list<
        boost::mp11::mp_list<char, ctu::Dimension<2>>,
        boost::mp11::mp_list<double, ctu::ZeroDimension>,
        boost::mp11::mp_list<int, ctu::Dimension<3>>>;
    using expected = boost::mp11::mp_list<
        boost::mp11::mp_list<char, ctu::Dimension<2>>,
        boost::mp11::mp_list<int, ctu::Dimension<3>>>;
    using actual = ctu::ud_operations::ZeroDimsRemover<input>::result;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected>);
}
