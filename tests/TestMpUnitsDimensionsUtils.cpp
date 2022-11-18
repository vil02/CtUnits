#define BOOST_TEST_MODULE TestMpUnitsDimensionsUtils

#include "../CtUnits/ctu/MpUnitsDimensionsUtils.hpp"
#include "../CtUnits/ctu/TypeConversionUtils.hpp"
#include "../CtUnits/ctu/UnitDimension.hpp"
#include <boost/mp11.hpp>
#include <boost/test/included/unit_test.hpp>
#include <boost/static_assert.hpp>

template <typename UnitDimensionA, typename UnitDimensionB>
struct IsLessInputType
{
    using input_a = ctu::tcu::UnitDimensionToUdPair<UnitDimensionA>;
    using input_b = ctu::tcu::UnitDimensionToUdPair<UnitDimensionB>;
};

struct TestUnitA {};
struct TestUnitB {};

using IsLessInputs = boost::mp11::mp_list<
    IsLessInputType<ctu::UnitDimension<bool, 1>,  ctu::UnitDimension<char, 10> >,
    IsLessInputType<ctu::UnitDimension<bool, 1>,  ctu::UnitDimension<char, -10> >,
    IsLessInputType<ctu::UnitDimension<char, -2>,  ctu::UnitDimension<int, 10> >,
    IsLessInputType<ctu::UnitDimension<bool, -20>,  ctu::UnitDimension<int, -5> >,
    IsLessInputType<ctu::UnitDimension<TestUnitA, -1>,  ctu::UnitDimension<TestUnitB, 1> >,
    IsLessInputType<ctu::UnitDimension<TestUnitA, 1>,  ctu::UnitDimension<TestUnitB, -1> > >;

BOOST_AUTO_TEST_CASE_TEMPLATE(TestIsLessPositive, IsLessInput, IsLessInputs)
{
      BOOST_STATIC_ASSERT(
          ctu::ud_operations::IsLess<typename IsLessInput::input_a, typename IsLessInput::input_b>());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(TestIsLessNegative, IsLessInput, IsLessInputs)
{
      BOOST_STATIC_ASSERT(
          !ctu::ud_operations::IsLess<typename IsLessInput::input_b, typename IsLessInput::input_a>());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(TestIsLessFunctionPositive, IsLessInput, IsLessInputs)
{
      const bool result = ctu::ud_operations::is_less<typename IsLessInput::input_a, typename IsLessInput::input_b>();
      BOOST_CHECK(result);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(TestIsLessFunctionNegative, IsLessInput, IsLessInputs)
{
  const bool result = !ctu::ud_operations::is_less<typename IsLessInput::input_b, typename IsLessInput::input_a>();
  BOOST_CHECK(result);
}
