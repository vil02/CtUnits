#ifndef MP_UNITS_DIMENSIONS_UTILS_HPP_INCLUDED
#define MP_UNITS_DIMENSIONS_UTILS_HPP_INCLUDED

#include "TypeConversionUtils.hpp"

#include <boost/mp11.hpp>
#include <boost/mp11/integral.hpp>
#include <boost/type_index.hpp>
#include <boost/type_index/ctti_type_index.hpp>

#include <type_traits>

using namespace boost::mp11;
using namespace boost::typeindex;

template <typename Map, typename Keys>
class FilterMap
{
    template <typename Key>
    using get_row = mp_map_find<Map, Key>;

public:
    using result = mp_transform<get_row, Keys>;
};

template <typename UnitDimA, typename UnitDimB>
constexpr bool is_less()
{
    return ctti_type_index::type_id_with_cvr<mp_first<UnitDimA> >() < ctti_type_index::type_id_with_cvr<mp_first<UnitDimB> >();
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
    using add_dims_common = mp_list<
        Unit,
        mp_plus<
            mp_second<mp_map_find<UnitsDimsA, Unit> >,
            mp_second<mp_map_find<UnitsDimsB, Unit> > > >;

    using common_unit_dims = mp_transform<add_dims_common, typename used_units::common>;

    using only_a_dims = typename FilterMap<
        UnitsDimsA,
        typename used_units::only_a>::result;

    using only_b_dims = typename FilterMap<
        UnitsDimsB,
        typename used_units::only_b>::result;

    template <typename UnitDimension>
    using dimension_is_not_zero = mp_bool<!std::is_same<mp_second<UnitDimension>, mp_int<0> >::value>;

    using result_b = mp_copy_if<
        mp_append<common_unit_dims, only_a_dims, only_b_dims>,
        dimension_is_not_zero >;

    using result = mp_sort<result_b, IsLess>;
    static_assert(mp_is_map<result>::value);
};

template <typename MpUnitDimension>
using minus_dim = mp_list<
    mp_first<MpUnitDimension>,
    mp_int<-mp_second<MpUnitDimension>::value > >;

template <typename MpUnitsDimensions>
using minus_dims = mp_transform<minus_dim, MpUnitsDimensions>;

namespace ctu::mp_units_dimensions_utils
{
    template <typename MpUnitsDimensionsA, typename MpUnitsDimensionsB>
    using add_mp_units_dims = typename AddUnitsDims<MpUnitsDimensionsA, MpUnitsDimensionsB>::result;

    template <typename MpUnitsDimensionsA, typename MpUnitsDimensionsB>
    using substract_mp_units_dims = add_mp_units_dims<MpUnitsDimensionsA, minus_dims<MpUnitsDimensionsB> >;

    template <template<typename, typename> typename F, typename UnitsDimensionsA, typename UnitsDimensionsB>
    using convert_and_transform = ::ctu::tcu::mp_list_to_units_dimensions<
        F<::ctu::tcu::units_dimensions_to_mp_list<UnitsDimensionsA>,
          ::ctu::tcu::units_dimensions_to_mp_list<UnitsDimensionsB> > >;

    template <typename UnitsDimensionsA, typename UnitsDimensionB>
    using add_units_dims = convert_and_transform<add_mp_units_dims, UnitsDimensionsA, UnitsDimensionB>;

    template <typename UnitsDimensionsA, typename UnitsDimensionB>
    using substract_units_dims = convert_and_transform<substract_mp_units_dims, UnitsDimensionsA, UnitsDimensionB>;
}
#endif // MP_UNITS_DIMENSIONS_UTILS_HPP_INCLUDED
