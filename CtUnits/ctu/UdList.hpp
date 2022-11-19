#ifndef UDLIST_HPP_INCLUDED
#define UDLIST_HPP_INCLUDED

#include <boost/mp11.hpp>

namespace ctu
{
template <typename... T> using UdList = boost::mp11::mp_list<T...>;
}
#endif // UDLIST_HPP_INCLUDED
