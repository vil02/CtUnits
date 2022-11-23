#ifndef UNITDIMENSION_HPP_INCLUDED
#define UNITDIMENSION_HPP_INCLUDED

#include "Dimension.hpp"
#include <boost/mp11.hpp>

namespace ctu
{
template <
    typename Unit, std::intmax_t DimNumerator, std::intmax_t DimDenominator = 1>
struct [[nodiscard]] UnitDimension
{
    static_assert(DimNumerator != 0);
    static_assert(DimDenominator != 0);
    using unit = Unit;
    using dimension = ctu::Dimension<DimNumerator, DimDenominator>;
};
} // namespace ctu
#endif // UNITDIMENSION_HPP_INCLUDED
