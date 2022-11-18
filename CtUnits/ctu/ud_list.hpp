#ifndef UD_LIST_HPP_INCLUDED
#define UD_LIST_HPP_INCLUDED

#include <boost/mp11.hpp>

namespace ctu
{
    template <typename... T>
    using ud_list = boost::mp11::mp_list<T...>;
}
#endif // UD_LIST_HPP_INCLUDED
