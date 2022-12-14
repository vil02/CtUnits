#ifndef QUANTITY_HPP_INCLUDED
#define QUANTITY_HPP_INCLUDED

#include "MpUnitsDimensionsUtils.hpp"
#include "UnitDimension.hpp"

#include "UdMap.hpp"

#include <cmath>

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

    template <typename Modification>
    constexpr Quantity<F, UnitsDimensions>&
    modify_value(const Modification& modification)
    {
        modification(this->value);
        return *this;
    }

  public:
    [[nodiscard]] constexpr explicit Quantity(const value_type& in_value)
        : value(in_value)
    {
    }

    [[nodiscard]] value_type get_value() const { return this->value; }

    constexpr Quantity<F, UnitsDimensions>&
    operator+=(const Quantity<F, UnitsDimensions>& other)
    {
        return this->modify_value(
            [other_value = other.get_value()](auto& this_value)
            { this_value += other_value; });
    }

    constexpr Quantity<F, UnitsDimensions>&
    operator-=(const Quantity<F, UnitsDimensions>& other)
    {
        return this->modify_value(
            [other_value = other.get_value()](auto& this_value)
            { this_value -= other_value; });
    }

    [[nodiscard]] constexpr Quantity<F, UnitsDimensions>
    operator+(const Quantity<F, UnitsDimensions>& other) const
    {
        return Quantity<F, UnitsDimensions>(
            this->get_value() + other.get_value());
    }

    [[nodiscard]] constexpr Quantity<F, UnitsDimensions>
    operator-(const Quantity<F, UnitsDimensions>& other) const
    {
        return Quantity<F, UnitsDimensions>(
            this->get_value() - other.get_value());
    }

    [[nodiscard]] constexpr Quantity<F, UnitsDimensions> operator-() const
    {
        return Quantity<F, UnitsDimensions>(-this->get_value());
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

    constexpr Quantity<F, UnitsDimensions>&
    operator*=(const Quantity<F, UdMap<>>& other)
    {
        return this->modify_value(
            [other_value = other.get_value()](auto& this_value)
            { this_value *= other_value; });
    }

    constexpr Quantity<F, UnitsDimensions>&
    operator/=(const Quantity<F, UdMap<>>& other)
    {
        return this->modify_value(
            [other_value = other.get_value()](auto& this_value)
            { this_value /= other_value; });
    }

    template <typename Power> [[nodiscard]] auto pow() const
    {
        using result_unit_dims =
            ctu::ud_operations::MultiplyUdMap<Power, UnitsDimensions>;
        using result_type = Quantity<F, result_unit_dims>;
        return result_type(static_cast<F>(std::pow(
            this->get_value(),
            static_cast<F>(Power::num) / static_cast<F>(Power::den))));
    }
};
} // namespace ctu
#endif // QUANTITY_HPP_INCLUDED
