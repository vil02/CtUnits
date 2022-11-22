#define BOOST_TEST_MODULE TestUnitsDimsRawAdder

#include "../CtUnits/ctu/MpUnitsDimensionsUtils.hpp"
#include "../CtUnits/ctu/UnitDimension.hpp"
#include <boost/mp11.hpp>
#include <boost/static_assert.hpp>
#include <boost/test/included/unit_test.hpp>

using ExampleMpUnitsDimsA = boost::mp11::mp_list<
    boost::mp11::mp_list<char, ctu::tcu::Dim<2>>,
    boost::mp11::mp_list<int, ctu::tcu::Dim<3>>>;

using ExampleMpUnitsDimsB = boost::mp11::mp_list<
    boost::mp11::mp_list<bool, ctu::tcu::Dim<3>>,
    boost::mp11::mp_list<int, ctu::tcu::Dim<4>>>;

BOOST_AUTO_TEST_CASE(TestUnitsDimsRawAdder)
{
    using expected = boost::mp11::mp_list<
        boost::mp11::mp_list<bool, ctu::tcu::Dim<3>>,
        boost::mp11::mp_list<char, ctu::tcu::Dim<2>>,
        boost::mp11::mp_list<int, ctu::tcu::Dim<7>>>;
    using actual = ctu::ud_operations::UnitsDimsRawAdder<
        ExampleMpUnitsDimsA, ExampleMpUnitsDimsB>::result;
    BOOST_STATIC_ASSERT(std::is_same_v<
                        ctu::ud_operations::SortMpUnitsDims<actual>,
                        ctu::ud_operations::SortMpUnitsDims<expected>>);
}

BOOST_AUTO_TEST_CASE(UnitsDimsRawAdderIsSymmetric)
{
    using result_a = typename ctu::ud_operations::UnitsDimsRawAdder<
        ExampleMpUnitsDimsA, ExampleMpUnitsDimsB>::result;
    using result_b = typename ctu::ud_operations::UnitsDimsRawAdder<
        ExampleMpUnitsDimsB, ExampleMpUnitsDimsA>::result;
    BOOST_STATIC_ASSERT(std::is_same_v<
                        ctu::ud_operations::SortMpUnitsDims<result_a>,
                        ctu::ud_operations::SortMpUnitsDims<result_b>>);
}
