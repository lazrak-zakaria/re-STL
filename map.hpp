

#ifndef FT_MAP_hpp__
#define FT_MAP_hpp__
#include <memory>
#include "rb_tree.hpp"



namespace ft
{

    template <class Pair>
    struct MapKeyOfT
    {
        const typename Pair::first_type &operator()(const Pair &p) const
        {
            return p.first;
        }
    };
    
    template <class Key, // map::key_type
              class T,
              class Compare = std::less<Key>,
              class Alloc = std::allocator<std::pair<const Key, T>>>
    class map : public ft::rb_tree<std::pair<const Key, T>, const Key, MapKeyOfT<std::pair<const Key, T>>, Compare, Alloc>
    {
    };
}

#endif
