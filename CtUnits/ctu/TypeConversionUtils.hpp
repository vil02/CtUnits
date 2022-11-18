#ifndef TYPE_CONVERSION_UTILS_HPP_INCLUDED
#define TYPE_CONVERSION_UTILS_HPP_INCLUDED

#include <boost/mp11.hpp>

#include "UnitDimension.hpp"

namespace ctu::tcu
{
    template <int Dimension>
    using dim_t = boost::mp11::mp_int<Dimension>;

    template <typename Unit, typename DimensionT>
    using ud_pair = boost::mp11::mp_list<Unit, DimensionT >;

    template <typename UnitDimension>
    using unit_dimension_to_ud_pair = ud_pair<
        typename UnitDimension::unit,
        boost::mp11::mp_int<UnitDimension::dimension> >;

    template <typename MpUnitDimension>
    using ud_pair_to_unit_dimension = UnitDimension<
        boost::mp11::mp_first<MpUnitDimension>,
        boost::mp11::mp_second<MpUnitDimension>::value>;

    template <typename UnitsDimensions>
    using units_dimensions_to_mp_list = boost::mp11::mp_transform<
        unit_dimension_to_ud_pair,
        UnitsDimensions>;

    template <typename MpUnitsDimensions>
    using mp_list_to_units_dimensions = boost::mp11::mp_transform<
        ud_pair_to_unit_dimension,
        MpUnitsDimensions>;
}

#endif // TYPE_CONVERSION_UTILS_HPP_INCLUDED
