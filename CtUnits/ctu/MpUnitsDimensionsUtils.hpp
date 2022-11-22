#ifndef MP_UNITS_DIMENSIONS_UTILS_HPP_INCLUDED
#define MP_UNITS_DIMENSIONS_UTILS_HPP_INCLUDED

#include "TypeConversionUtils.hpp"

#include <boost/mp11.hpp>
#include <boost/type_index/ctti_type_index.hpp>

#include <type_traits>

namespace ctu::ud_operations
{
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

template <typename MpUnitsDims>
using SortMpUnitsDims = boost::mp11::mp_sort<MpUnitsDims, IsLess>;

template <typename MpUnitsDims> class IsValidMpUnitsDims
{
    static constexpr auto is_map = boost::mp11::mp_is_map<MpUnitsDims>::value;
    using mp_units_dims_sorted = boost::mp11::mp_sort<MpUnitsDims, IsLess>;
    static constexpr auto is_sorted =
        std::is_same_v<MpUnitsDims, mp_units_dims_sorted>;

  public:
    static constexpr bool value = is_map && is_sorted;
};

template <typename MpUnitsDims, typename Unit>
using QueryUnitDim = boost::mp11::mp_if<
    boost::mp11::mp_map_contains<MpUnitsDims, Unit>,
    boost::mp11::mp_map_find<MpUnitsDims, Unit>,
    ctu::tcu::UdPair<Unit, ctu::tcu::Dim<0>>>;

template <typename MpUnitsDims, typename Unit>
using QueryDim = GetDimType<QueryUnitDim<MpUnitsDims, Unit>>;

template <typename MpUnitsDimsA, typename MpUnitsDimsB> class UnitsDimsRawAdder
{
    using used_units = boost::mp11::mp_set_union<
        boost::mp11::mp_map_keys<MpUnitsDimsA>,
        boost::mp11::mp_map_keys<MpUnitsDimsB>>;

    template <typename Unit>
    using add_dims = ctu::tcu::UdPair<
        Unit, boost::mp11::mp_plus<
                  QueryDim<MpUnitsDimsA, Unit>, QueryDim<MpUnitsDimsB, Unit>>>;

  public:
    using result = boost::mp11::mp_transform<add_dims, used_units>;
};

template <typename MpUnitsDims> class ZeroDimsRemover
{
    template <typename UnitDim>
    using dimension_is_not_zero = boost::mp11::mp_bool<
        !std::is_same_v<GetDimType<UnitDim>, ctu::tcu::Dim<0>>>;

  public:
    using result = boost::mp11::mp_copy_if<MpUnitsDims, dimension_is_not_zero>;
};

template <typename MpUnitsDimsA, typename MpUnitsDimsB> class UnitsDimsAdder
{
    using raw_sum_of_units_dims =
        typename UnitsDimsRawAdder<MpUnitsDimsA, MpUnitsDimsB>::result;

    using result_not_sorted =
        typename ZeroDimsRemover<raw_sum_of_units_dims>::result;

  public:
    using result = SortMpUnitsDims<result_not_sorted>;
    static_assert(IsValidMpUnitsDims<result>::value);
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
