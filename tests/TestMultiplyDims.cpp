#define BOOST_TEST_MODULE TestMultiplyDims

#include "../CtUnits/ctu/MpUnitsDimensionsUtils.hpp"
#include "../CtUnits/ctu/UnitDimension.hpp"
#include <boost/mp11.hpp>
#include <boost/static_assert.hpp>
#include <boost/test/included/unit_test.hpp>
#include <ratio>

using ExampleMpUnitsDims = boost::mp11::mp_list<
    boost::mp11::mp_list<bool, ctu::Dimension<2, 3>>,
    boost::mp11::mp_list<char, ctu::Dimension<-2, 4>>,
    boost::mp11::mp_list<int, ctu::Dimension<3, 2>>>;

BOOST_AUTO_TEST_CASE(MultiplyByProperFraction)
{
    using multiplier = std::ratio<1, 2>;
    using expected = boost::mp11::mp_list<
        boost::mp11::mp_list<bool, ctu::Dimension<1, 3>>,
        boost::mp11::mp_list<char, ctu::Dimension<-1, 4>>,
        boost::mp11::mp_list<int, ctu::Dimension<3, 4>>>;
    using actual =
        ctu::ud_operations::MultiplyDims<multiplier, ExampleMpUnitsDims>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected>);
}

BOOST_AUTO_TEST_CASE(MultiplyByImproperFraction)
{
    using multiplier = std::ratio<-2, 6>;
    using expected = boost::mp11::mp_list<
        boost::mp11::mp_list<bool, ctu::Dimension<-2, 9>>,
        boost::mp11::mp_list<char, ctu::Dimension<1, 6>>,
        boost::mp11::mp_list<int, ctu::Dimension<-1, 2>>>;
    using actual =
        ctu::ud_operations::MultiplyDims<multiplier, ExampleMpUnitsDims>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected>);
}

BOOST_AUTO_TEST_CASE(MultiplyByZero)
{
    using multiplier = std::ratio<0>;
    using expected = boost::mp11::mp_list<>;
    using actual =
        ctu::ud_operations::MultiplyDims<multiplier, ExampleMpUnitsDims>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected>);
}

BOOST_AUTO_TEST_CASE(CheckMinusDims)
{
    using expected = boost::mp11::mp_list<
        boost::mp11::mp_list<bool, ctu::Dimension<-2, 3>>,
        boost::mp11::mp_list<char, ctu::Dimension<1, 2>>,
        boost::mp11::mp_list<int, ctu::Dimension<-3, 2>>>;
    using actual = ctu::ud_operations::MinusDims<ExampleMpUnitsDims>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected>);
}
