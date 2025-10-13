#include <memory>

#include"hash_table.hpp"

namespace ft
{

    template<class Pair>
    struct MapKeyOfT
    {
        const typename Pair::first_type& operator()(const Pair& p) const noexcept
        {
            return p.first;
        }
    };
    
    template<
        class Key,
        class T,
        class Hash = std::hash<Key>,
        class KeyEqual = std::equal_to<Key>,
        class Allocator = std::allocator<std::pair<const Key, T>>
    > class unordered_map :  public ft::hash_table<std::pair<const Key, T>, Key, MapKeyOfT<std::pair<const Key, T>>,Hash, KeyEqual, Allocator, true >
    {


    };

}


