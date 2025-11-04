#ifndef FT_HASH_SET_HPP
#define FT_HASH_SET_HPP

#include <memory>
#include "hash_table.hpp"

namespace ft
{
    template <class K>
    struct SetKeyOfT
    {
        const K &operator()(const K &key) const
        {
            return key;
        }
    };

    template <class Key,                        // unordered_set::key_type/value_type
              class Hash = std::hash<Key>,      // unordered_set::hasher
              class Pred = std::equal_to<Key>,  // unordered_set::key_equal
              class Alloc = std::allocator<Key> // unordered_set::allocator_type
              >
    class unordered_set : public hash_table<Key, Key, SetKeyOfT<Key>, Hash, Pred, Alloc, true>
    {
    private:
        typedef hash_table<Key, Key, SetKeyOfT<Key>, Hash, Pred, Alloc, true> hash_table_type;

    public:
        explicit unordered_set(size_t bucket_count = 13,
                               const Hash &hash = Hash(),
                               const Pred &equal = Pred(),
                               const Alloc &alloc = Alloc()) : hash_table_type(bucket_count,
                                                                               hash,
                                                                               equal,
                                                                               alloc)

        {
        }

        template <class InputIt>
        unordered_set(InputIt first, InputIt last,
                      size_t bucket_count = 13,
                      const Hash &hash = Hash(),
                      const Pred &equal = Pred(),
                      const Alloc &alloc = Alloc()) : hash_table_type(first,
                                                                      last,
                                                                      bucket_count,
                                                                      hash,
                                                                      equal,
                                                                      alloc)

        {
        }

        unordered_set(const unordered_set &other) : hash_table_type(
                                                        other)
        {
        }

        unordered_set(const unordered_set &other, const Alloc &alloc) : hash_table_type(
                                                                            other)
        {
        }

        ~unordered_set()
        {
        }
    };

    template <class Key,                        // unordered_multiset::key_type/value_type
              class Hash = std::hash<Key>,      // unordered_multiset::hasher
              class Pred = std::equal_to<Key>,  // unordered_multiset::key_equal
              class Alloc = std::allocator<Key> // unordered_multiset::allocator_type
              >
    class unordered_multiset : public hash_table<Key, Key, SetKeyOfT<Key>, Hash, Pred, Alloc, true>
    {
    private:
        typedef hash_table<Key, Key, SetKeyOfT<Key>, Hash, Pred, Alloc, true> hash_table_type;

    public:
        explicit unordered_multiset(size_t bucket_count = 13,
                                    const Hash &hash = Hash(),
                                    const Pred &equal = Pred(),
                                    const Alloc &alloc = Alloc()) : hash_table_type(bucket_count,
                                                                                    hash,
                                                                                    equal,
                                                                                    alloc)
        {
        }

        template <class InputIt>
        unordered_multiset(InputIt first, InputIt last,
                           size_t bucket_count = 13,
                           const Hash &hash = Hash(),
                           const Pred &equal = Pred(),
                           const Alloc &alloc = Alloc()) : hash_table_type(first,
                                                                           last,
                                                                           bucket_count,
                                                                           hash,
                                                                           equal,
                                                                           alloc)
        {
        }

        unordered_multiset(const unordered_multiset &other) : hash_table_type(other)
        {
        }

        unordered_multiset(const unordered_multiset &other, const Alloc &alloc) : hash_table_type(other)
        {
        }

        ~unordered_multiset()
        {
        }
    };

}

#endif