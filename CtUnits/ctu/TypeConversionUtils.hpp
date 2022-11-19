#ifndef TYPE_CONVERSION_UTILS_HPP_INCLUDED
#define TYPE_CONVERSION_UTILS_HPP_INCLUDED

#include <boost/mp11.hpp>

#include "UnitDimension.hpp"

namespace ctu::tcu
{
template <int Dimension> using Dim = boost::mp11::mp_int<Dimension>;

template <typename Unit, typename DimensionT>
using UdPair = boost::mp11::mp_list<Unit, DimensionT>;

template <typename UnitDimension>
using UnitDimensionToUdPair = UdPair<
    typename UnitDimension::unit,
    boost::mp11::mp_int<UnitDimension::dimension>>;

template <typename MpUnitDimension>
using UdPairToUnitDimension = UnitDimension<
    boost::mp11::mp_first<MpUnitDimension>,
    boost::mp11::mp_second<MpUnitDimension>::value>;

template <typename UnitsDimensions>
using UdMapToMpList =
    boost::mp11::mp_transform<UnitDimensionToUdPair, UnitsDimensions>;

template <typename MpUnitsDimensions>
using MpListToUdMap =
    boost::mp11::mp_transform<UdPairToUnitDimension, MpUnitsDimensions>;
} // namespace ctu::tcu

#endif // TYPE_CONVERSION_UTILS_HPP_INCLUDED
