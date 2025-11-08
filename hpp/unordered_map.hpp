#include <memory>

#include "hash_table.hpp"
#include "functional.hpp"
#include "stdexcept.hpp"
#ifndef FT_HASH_MAP_HPP
#define FT_HASH_MAP_HPP

namespace ft
{



    template <class Key,
              class T,
              class Hash = ft::HashFunc<Key>,
              class Pred = ft::equal_to<Key>,
              class Alloc = std::allocator<ft::pair<const Key, T> > >
    class unordered_map : public hash_table<ft::pair<const Key, T>, Key, ft::MapKeyOfT<ft::pair<const Key, T> >, Hash, Pred, Alloc, true>
    {
    private:
        typedef hash_table<ft::pair<const Key, T>, Key, ft::MapKeyOfT<ft::pair<const Key, T> >, Hash, Pred, Alloc, true> hash_table_type;

    public:
        typedef T mapped_type; //            = T;
        explicit unordered_map(size_t bucket_count = 13,
                               const Hash &hash = Hash(),
                               const Pred &equal = Pred(),
                               const Alloc &alloc = Alloc()) : hash_table_type(bucket_count,
                                                                               hash,
                                                                               equal,
                                                                               alloc)
        {
        }

        template <class InputIt>
        unordered_map(InputIt first, InputIt last,
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

        unordered_map(const unordered_map &other) : hash_table_type(other)
        {
        }
        explicit unordered_map ( const Alloc& alloc ) : hash_table_type(alloc)
        {

        }

        unordered_map(const unordered_map &other, const Alloc &alloc) : hash_table_type(other, alloc)
        {
        }

        ~unordered_map()
        {
        }

        T &at(const Key &key)
        {
            typename hash_table_type::iterator it = this->find(key);
            if (it == this->end())
                throw ft::out_of_range("pos is out of range");
            return it->second;
        }

        const T &at(const Key &key) const
        {
            typename hash_table_type::iterator it = this->find(key);
            if (it == this->end())
                throw ft::out_of_range("pos is out of range");
            return it->second;
        }

        T &operator[](const Key &key)
        {
            typename hash_table_type::iterator it = this->find(key);
            if (it == this->end())
                it = this->insert(ft::make_pair(key, T())).first;
            return it->second;
        }
    };

    template <class Key,
              class T,
              class Hash = ft::HashFunc<Key>,
              class Pred = ft::equal_to<Key>,
              class Alloc = std::allocator<ft::pair<const Key, T> > >
    class unordered_multimap : public hash_table<ft::pair<const Key, T>, Key, ft::MapKeyOfT<ft::pair<const Key, T> >, Hash, Pred, Alloc, false>
    {
    private:
        typedef hash_table<ft::pair<const Key, T>, Key, ft::MapKeyOfT<ft::pair<const Key, T> >, Hash, Pred, Alloc, false> hash_table_type;

    public:
        typedef T mapped_type; //            = T;
        explicit unordered_multimap(size_t bucket_count = 13,
                                    const Hash &hash = Hash(),
                                    const Pred &equal = Pred(),
                                    const Alloc &alloc = Alloc()) : hash_table_type(bucket_count,
                                                                                    hash,
                                                                                    equal,
                                                                                    alloc)
        {
        }
        explicit unordered_multimap ( const Alloc& alloc ) : hash_table_type(alloc)
        {

        }
        template <class InputIt>
        unordered_multimap(InputIt first, InputIt last,
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

        unordered_multimap(const unordered_multimap &other) : hash_table_type(other)
        {
        }

        unordered_multimap(const unordered_multimap &other, const Alloc &alloc) : hash_table_type(other, alloc)
        {
        }

        ~unordered_multimap()
        {
        }

        T &at(const Key &key)
        {
            typename hash_table_type::iterator it = this->find(key);
            if (it == this->end())
                throw ft::out_of_range("pos is out of range");
            return it->second;
        }

        const T &at(const Key &key) const
        {
            typename hash_table_type::iterator it = this->find(key);
            if (it == this->end())
                throw ft::out_of_range("pos is out of range");
            return it->second;
        }

        T &operator[](const Key &key)
        {
            typename hash_table_type::iterator it = this->find(key);
            if (it == this->end())
                it = this->insert(ft::make_pair(key, T())).first;
            return it->second;
        }
    };

    template <class Key,
              class T,
              class Hash,
              class Pred,
              class Alloc>
    void swap(ft::unordered_map<Key, T,  Hash,
                                 Pred,
                                 Alloc> &lhs,
              ft::unordered_map<Key, T,  Hash,
                                 Pred,
                                 Alloc> &rhs)
    {
        lhs.swap(rhs);
    }

    template <class Key,
              class T,
              class Hash,
              class Pred,
              class Alloc>
    void swap(ft::unordered_multimap<Key, T,  Hash,
                                 Pred,
                                 Alloc> &lhs,
              ft::unordered_multimap<Key, T,  Hash,
                                 Pred,
                                 Alloc> &rhs)
    {
        lhs.swap(rhs);
    }

}
#endif