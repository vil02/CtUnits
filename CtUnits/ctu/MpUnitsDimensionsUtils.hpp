#ifndef MP_UNITS_DIMENSIONS_UTILS_HPP_INCLUDED
#define MP_UNITS_DIMENSIONS_UTILS_HPP_INCLUDED

#include "TypeConversionUtils.hpp"

#include <boost/mp11.hpp>
#include <boost/type_index/ctti_type_index.hpp>

#include <type_traits>

namespace ctu::ud_operations
{
template <typename Map, typename Keys> class GetRows
{
    template <typename Key> using get_row = boost::mp11::mp_map_find<Map, Key>;

  public:
    using result = boost::mp11::mp_transform<get_row, Keys>;
};

template <typename MpUnitDim> using GetUnit = boost::mp11::mp_first<MpUnitDim>;

template <typename MpUnitDim>
using GetDimType = boost::mp11::mp_second<MpUnitDim>;

template <typename MpUnitDim> constexpr auto GetUnitId()
{
    return boost::typeindex::ctti_type_index::type_id_with_cvr<
        GetUnit<MpUnitDim>>();
}

template <typename MpUnitDimA, typename MpUnitDimB> constexpr bool is_less()
{
    constexpr auto id_a = GetUnitId<MpUnitDimA>();
    constexpr auto id_b = GetUnitId<MpUnitDimB>();
    static_assert(id_a != id_b);
    return id_a < id_b;
}

template <typename MpUnitDimA, typename MpUnitDimB>
using IsLess = boost::mp11::mp_bool<is_less<MpUnitDimA, MpUnitDimB>()>;

template <typename MpUnitsDimsA, typename MpUnitsDimsB> class UsedUnits
{
    using units_a = boost::mp11::mp_map_keys<MpUnitsDimsA>;
    using units_b = boost::mp11::mp_map_keys<MpUnitsDimsB>;

  public:
    using common = boost::mp11::mp_set_intersection<units_a, units_b>;
    using only_a = boost::mp11::mp_set_difference<units_a, units_b>;
    using only_b = boost::mp11::mp_set_difference<units_b, units_a>;
};

template <typename MpUnitsDimsA, typename MpUnitsDimsB> class UnitsDimsAdder
{
    using used_units = UsedUnits<MpUnitsDimsA, MpUnitsDimsB>;
    template <typename Unit>
    using add_dims_common = ctu::tcu::UdPair<
        Unit, boost::mp11::mp_plus<
                  GetDimType<boost::mp11::mp_map_find<MpUnitsDimsA, Unit>>,
                  GetDimType<boost::mp11::mp_map_find<MpUnitsDimsB, Unit>>>>;

    using common_unit_dims =
        boost::mp11::mp_transform<add_dims_common, typename used_units::common>;

    using only_a_dims =
        typename GetRows<MpUnitsDimsA, typename used_units::only_a>::result;

    using only_b_dims =
        typename GetRows<MpUnitsDimsB, typename used_units::only_b>::result;

    template <typename UnitDimension>
    using dimension_is_not_zero = boost::mp11::mp_bool<
        !std::is_same_v<GetDimType<UnitDimension>, ctu::tcu::Dim<0>>>;

    using result_not_sorted = boost::mp11::mp_copy_if<
        boost::mp11::mp_append<common_unit_dims, only_a_dims, only_b_dims>,
        dimension_is_not_zero>;

  public:
    using result = boost::mp11::mp_sort<result_not_sorted, IsLess>;
    static_assert(boost::mp11::mp_is_map<result>::value);
};

template <typename MpUnitDimension>
using MinusDim = ctu::tcu::UdPair<
    GetUnit<MpUnitDimension>,
    ::ctu::tcu::Dim<-GetDimType<MpUnitDimension>::value>>;

template <typename MpUnitsDims>
using MinusDims = boost::mp11::mp_transform<MinusDim, MpUnitsDims>;

template <typename MpUnitsDimsA, typename MpUnitsDimsB>
using AddMpUnitsDims =
    typename UnitsDimsAdder<MpUnitsDimsA, MpUnitsDimsB>::result;

template <typename MpUnitsDimsA, typename MpUnitsDimsB>
using SubstractMpUnitsDims =
    AddMpUnitsDims<MpUnitsDimsA, MinusDims<MpUnitsDimsB>>;

template <
    template <typename, typename> typename F, typename UdMapA, typename UdMapB>
using convert_and_transform = ::ctu::tcu::MpListToUdMap<
    F<::ctu::tcu::UdMapToMpList<UdMapA>, ::ctu::tcu::UdMapToMpList<UdMapB>>>;

template <typename UdMapA, typename UdMapB>
using AddUdMaps = convert_and_transform<AddMpUnitsDims, UdMapA, UdMapB>;

template <typename UdMapA, typename UdMapB>
using SubstractUdMaps =
    convert_and_transform<SubstractMpUnitsDims, UdMapA, UdMapB>;
} // namespace ctu::ud_operations
#endif // MP_UNITS_DIMENSIONS_UTILS_HPP_INCLUDED
