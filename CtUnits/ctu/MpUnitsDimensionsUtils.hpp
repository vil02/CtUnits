#ifndef MP_UNITS_DIMENSIONS_UTILS_HPP_INCLUDED
#define MP_UNITS_DIMENSIONS_UTILS_HPP_INCLUDED

#include "TypeConversionUtils.hpp"

#include <boost/mp11.hpp>
#include <boost/type_index/ctti_type_index.hpp>

#include <type_traits>

using namespace boost::mp11;
using namespace boost::typeindex;

template <typename Map, typename Keys>
class GetRows
{
    template <typename Key>
    using get_row = mp_map_find<Map, Key>;

public:
    using result = mp_transform<get_row, Keys>;
};

template <typename UnitDim>
constexpr auto GetUnitId()
{
    return ctti_type_index::type_id_with_cvr<mp_first<UnitDim> >();
}

template <typename UnitDimA, typename UnitDimB>
constexpr bool is_less()
{
    return GetUnitId<UnitDimA>() < GetUnitId<UnitDimB>();
}

template <typename UnitDimA, typename UnitDimB>
using IsLess = mp_bool<is_less<UnitDimA, UnitDimB>()>;

template <typename UnitsDimsA, typename UnitsDimsB>
class UsedUnits
{
    using units_a = mp_map_keys<UnitsDimsA>;
    using units_b = mp_map_keys<UnitsDimsB>;

public:
    using common = mp_set_intersection<units_a, units_b>;
    using only_a = mp_set_difference<units_a, units_b>;
    using only_b = mp_set_difference<units_b, units_a>;
};

template <typename UnitsDimsA, typename UnitsDimsB>
struct AddUnitsDims
{
    using used_units = UsedUnits<UnitsDimsA, UnitsDimsB>;
    template <typename Unit>
    using add_dims_common = ctu::tcu::UdPair<
        Unit,
        mp_plus<
            mp_second<mp_map_find<UnitsDimsA, Unit> >,
            mp_second<mp_map_find<UnitsDimsB, Unit> > > >;

    using common_unit_dims = mp_transform<add_dims_common, typename used_units::common>;

    using only_a_dims = typename GetRows<
        UnitsDimsA,
        typename used_units::only_a>::result;

    using only_b_dims = typename GetRows<
        UnitsDimsB,
        typename used_units::only_b>::result;

    template <typename UnitDimension>
    using dimension_is_not_zero = mp_bool<!std::is_same<mp_second<UnitDimension>, ctu::tcu::Dim<0> >::value>;

    using result_b = mp_copy_if<
        mp_append<common_unit_dims, only_a_dims, only_b_dims>,
        dimension_is_not_zero>;

    using result = mp_sort<result_b, IsLess>;
    static_assert(mp_is_map<result>::value);
};

template <typename MpUnitDimension>
using MinusDim = ctu::tcu::UdPair<
    mp_first<MpUnitDimension>,
    ctu::tcu::Dim<-mp_second<MpUnitDimension>::value > >;

template <typename MpUnitsDimensions>
using MinusDims = mp_transform<MinusDim, MpUnitsDimensions>;

namespace ctu::mp_units_dimensions_utils
{
    template <typename MpUnitsDimensionsA, typename MpUnitsDimensionsB>
    using add_mp_units_dims = typename AddUnitsDims<MpUnitsDimensionsA, MpUnitsDimensionsB>::result;

    template <typename MpUnitsDimensionsA, typename MpUnitsDimensionsB>
    using substract_mp_units_dims = add_mp_units_dims<MpUnitsDimensionsA, MinusDims<MpUnitsDimensionsB> >;

    template <template<typename, typename> typename F, typename UnitsDimensionsA, typename UnitsDimensionsB>
    using convert_and_transform = ::ctu::tcu::MpListToUdList<
        F<::ctu::tcu::UdListToMpList<UnitsDimensionsA>,
          ::ctu::tcu::UdListToMpList<UnitsDimensionsB> > >;

    template <typename UnitsDimensionsA, typename UnitsDimensionB>
    using add_units_dims = convert_and_transform<add_mp_units_dims, UnitsDimensionsA, UnitsDimensionB>;

    template <typename UnitsDimensionsA, typename UnitsDimensionB>
    using substract_units_dims = convert_and_transform<substract_mp_units_dims, UnitsDimensionsA, UnitsDimensionB>;
}
#endif // MP_UNITS_DIMENSIONS_UTILS_HPP_INCLUDED
