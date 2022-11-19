#ifndef UNITDIMENSION_HPP_INCLUDED
#define UNITDIMENSION_HPP_INCLUDED

#include <boost/mp11.hpp>

namespace ctu
{
template <typename Unit, int Dimension> struct [[nodiscard]] UnitDimension
{
    static_assert(Dimension != 0);
    using unit = Unit;
    static constexpr auto dimension = Dimension;
};
} // namespace ctu
#endif // UNITDIMENSION_HPP_INCLUDED
