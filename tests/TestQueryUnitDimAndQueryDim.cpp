#define BOOST_TEST_MODULE TestQueryUnitDimAndQueryDim

#include "../CtUnits/ctu/MpUnitsDimensionsUtils.hpp"
#include "../CtUnits/ctu/UnitDimension.hpp"
#include <boost/mp11.hpp>
#include <boost/static_assert.hpp>
#include <boost/test/included/unit_test.hpp>

using ExampleMpUnitsDims = boost::mp11::mp_list<
    boost::mp11::mp_list<bool, ctu::Dimension<10>>,
    boost::mp11::mp_list<char, ctu::Dimension<-20>>,
    boost::mp11::mp_list<int, ctu::Dimension<30>>>;

BOOST_AUTO_TEST_CASE(QueryUnitDimForExistingUnit)
{
    using expected = boost::mp11::mp_list<char, ctu::Dimension<-20>>;
    using actual = ctu::ud_operations::QueryUnitDim<ExampleMpUnitsDims, char>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected>);
}

BOOST_AUTO_TEST_CASE(QueryUnitDimForNonExistingUnit)
{
    using expected = boost::mp11::mp_list<double, ctu::ZeroDimension>;
    using actual = ctu::ud_operations::QueryUnitDim<ExampleMpUnitsDims, double>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected>);
}

BOOST_AUTO_TEST_CASE(QueryDimForExistingUnit)
{
    using expected = ctu::Dimension<30>;
    using actual = ctu::ud_operations::QueryDim<ExampleMpUnitsDims, int>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, expected>);
}

BOOST_AUTO_TEST_CASE(QueryDimForNonExistingUnit)
{
    using actual = ctu::ud_operations::QueryDim<ExampleMpUnitsDims, float>;
    BOOST_STATIC_ASSERT(std::is_same_v<actual, ctu::ZeroDimension>);
}
