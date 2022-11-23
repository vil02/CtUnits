#ifndef DIMENSION_HPP_INCLUDED
#define DIMENSION_HPP_INCLUDED

#include <ratio>

namespace ctu
{
template <std::intmax_t Numerator, std::intmax_t Denominator = 1>
using Dimension = std::ratio<Numerator, Denominator>;

using ZeroDimension = Dimension<0>;

template <typename Dimension>
using IsDimensionIsNotZero = std::ratio_not_equal<Dimension, ZeroDimension>;

template <typename DimensionA, typename DimensionB>
using AddDimensions = std::ratio_add<DimensionA, DimensionB>;

template <typename Dimension>
using MinusDimension = std::ratio_subtract<ZeroDimension, Dimension>;

template <typename DimensionA, typename DimensionB>
using MultiplyDimensions = std::ratio_multiply<DimensionA, DimensionB>;
} // namespace ctu
#endif // DIMENSION_HPP_INCLUDED
