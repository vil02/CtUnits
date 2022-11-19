#ifndef QUANTITY_HPP_INCLUDED
#define QUANTITY_HPP_INCLUDED

#include "MpUnitsDimensionsUtils.hpp"
#include "UnitDimension.hpp"

#include "UdMap.hpp"

namespace ctu
{
template <typename F, typename UnitsDimensions> class [[nodiscard]] Quantity
{
    static_assert(ud_operations::IsValidMpUnitsDims<
                  tcu::UdMapToMpList<UnitsDimensions>>::value);

  public:
    using value_type = F;

  private:
    value_type value;

  public:
    [[nodiscard]] constexpr explicit Quantity(const value_type& in_value)
        : value(in_value)
    {
    }

    [[nodiscard]] value_type get_value() const { return this->value; }

    [[nodiscard]] constexpr Quantity<F, UnitsDimensions>
    operator+(const Quantity<F, UnitsDimensions>& other) const
    {
        return Quantity(this->get_value() + other.get_value());
    }

    [[nodiscard]] constexpr Quantity<F, UnitsDimensions>
    operator-(const Quantity<F, UnitsDimensions>& other) const
    {
        return Quantity(this->get_value() - other.get_value());
    }

    template <typename OtherUnitsDimensions>
    [[nodiscard]] constexpr auto
    operator*(const Quantity<F, OtherUnitsDimensions>& other) const
    {
        using result_units_dims = ctu::ud_operations::AddUdMaps<
            UnitsDimensions, OtherUnitsDimensions>;
        using result_type = Quantity<F, result_units_dims>;
        return result_type(this->get_value() * other.get_value());
    }

    template <typename OtherUnitsDimensions>
    [[nodiscard]] constexpr auto
    operator/(const Quantity<F, OtherUnitsDimensions>& other) const
    {
        using result_units_dims = ctu::ud_operations::SubstractUdMaps<
            UnitsDimensions, OtherUnitsDimensions>;
        using result_type = Quantity<F, result_units_dims>;
        return result_type(this->get_value() / other.get_value());
    }
};
} // namespace ctu
#endif // QUANTITY_HPP_INCLUDED
