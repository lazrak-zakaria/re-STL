#ifndef FT_HASH_SET_HPP
#define FT_HASH_SET_HPP

#include <memory>
#include "hash_table.hpp"

namespace ft
{
    template <class Key,                   // unordered_set::key_type/value_type
              class Hash = std::hash<Key>,      // unordered_set::hasher
              class Pred = std::equal_to<Key>,  // unordered_set::key_equal
              class Alloc = std::allocator<Key> // unordered_set::allocator_type
              >
    class unordered_set : public hash_table<const Key, Hash, Pred, Alloc, true>
    {

    } ;

}

#endif