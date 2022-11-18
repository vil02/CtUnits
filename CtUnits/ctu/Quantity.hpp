#ifndef QUANTITY_HPP_INCLUDED
#define QUANTITY_HPP_INCLUDED

#include <boost/mp11.hpp>

#include "UnitDimension.hpp"
#include "./MpUnitsDimensionsUtils.hpp"

#include "ud_list.hpp"


namespace ctu
{
    template <typename F, typename UnitsDimensions>
    class [[nodiscard]] Quantity
    {
        static_assert(
            boost::mp11::mp_is_map<tcu::units_dimensions_to_mp_list<UnitsDimensions> >::value);

    public:
        using value_type = F;

    private:
        value_type value;

    public:
        [[nodiscard]] constexpr explicit Quantity(
            const value_type& in_value) : value(in_value)
        {}

        [[nodiscard]] value_type get_value() const
        {
            return this->value;
        }

        [[nodiscard]] constexpr Quantity<F, UnitsDimensions> operator+(
                const Quantity<F, UnitsDimensions>& other) const
        {
            return Quantity(this->get_value()+other.get_value());
        }

        [[nodiscard]] constexpr Quantity<F, UnitsDimensions> operator-(
                const Quantity<F, UnitsDimensions>& other) const
        {
            return Quantity(this->get_value()-other.get_value());
        }

        template <typename OtherUnitsDimensions>
        [[nodiscard]] constexpr auto operator*(
               const Quantity<F, OtherUnitsDimensions>& other) const
        {
           using result_units_dims = mp_units_dimensions_utils::add_units_dims<
               UnitsDimensions, OtherUnitsDimensions>;
           using result_type = Quantity<F, result_units_dims>;
           return result_type(this->get_value()*other.get_value());
        }

        template <typename OtherUnitsDimensions>
        [[nodiscard]] constexpr auto operator/(
               const Quantity<F, OtherUnitsDimensions>& other) const
        {
           using result_units_dims = mp_units_dimensions_utils::substract_units_dims<
               UnitsDimensions, OtherUnitsDimensions>;
           using result_type = Quantity<F, result_units_dims>;
           return result_type(this->get_value()/other.get_value());
        }

    };
}
#endif // QUANTITY_HPP_INCLUDED
