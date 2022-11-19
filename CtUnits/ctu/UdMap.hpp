#ifndef UDMAP_HPP_INCLUDED
#define UDMAP_HPP_INCLUDED

#include "MpUnitsDimensionsUtils.hpp"
#include "TypeConversionUtils.hpp"
#include <boost/mp11.hpp>
#include <type_traits>

namespace ctu
{
template <typename... T> struct GetUdMap
{
    using result = boost::mp11::mp_list<T...>;

    static_assert(ud_operations::IsValidMpUnitsDims<
                  ::ctu::tcu::UdMapToMpList<result>>::value);
};

template <typename... T> using UdMap = typename GetUdMap<T...>::result;
} // namespace ctu
#endif // UDMAP_HPP_INCLUDED
