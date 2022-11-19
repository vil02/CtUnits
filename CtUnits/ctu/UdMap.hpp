#ifndef UDMAP_HPP_INCLUDED
#define UDMAP_HPP_INCLUDED

#include <boost/mp11.hpp>

namespace ctu
{
template <typename... T> using UdMap = boost::mp11::mp_list<T...>;
}
#endif // UDMAP_HPP_INCLUDED
