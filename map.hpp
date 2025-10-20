

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
        typedef ft::rb_tree<std::pair<const Key, T>, const Key, MapKeyOfT<std::pair<const Key, T>>, Compare, Alloc> rb_tree;

    public:
        class value_compare
        {
        protected:
            Compare comp;
            value_compare(Compare c)
                : comp(c)
            {
            }

        public:
            bool operator()(const typename rb_tree::value_type &x, const  typename rb_tree::value_type &y) const
            {
                return comp(x.first, y.first);
            }
        };

        T &at(const Key &key)
        {
            typename rb_tree::iterator it = this->find(key);
            if (it == this->end())
                throw std::out_of_range("not found");
            return it->second;
        }

        const T &at(const Key &key) const
        {
            typename rb_tree::iterator it = this->find(key);
            if (it == this->end())
                throw std::out_of_range("pos is out of range");
            return it->second;
        }

        T &operator[](const Key &key)
        {
            typename rb_tree::iterator it = this->find(key);
            if (it == this->end())
                it = this->insert(std::make_pair(key, T())).first;
            return it->second;
        }

        value_compare value_comp() const
        {
            return value_compare();
        }
    };

    template <class Key, // map::key_type
              class T,
              class Compare = std::less<Key>,
              class Alloc = std::allocator<std::pair<const Key, T>>>
    class multimap : public ft::rb_tree<std::pair<const Key, T>, const Key, MapKeyOfT<std::pair<const Key, T>>, Compare, Alloc, false>
    {
        typedef ft::rb_tree<std::pair<const Key, T>, const Key, MapKeyOfT<std::pair<const Key, T>>, Compare, Alloc, false> rb_tree;

    public:
        class value_compare
        {
        protected:
            Compare comp;
            value_compare(Compare c)
                : comp(c)
            {
            }

        public:
            bool operator()(const typename rb_tree::value_type &x, const  typename rb_tree::value_type &y) const
            {
                return comp(x.first, y.first);
            }
        };

        T &at(const Key &key)
        {
            typename rb_tree::iterator it = this->find(key);
            if (it == this->end())
                throw std::out_of_range("not found");
            return it->second;
        }

        const T &at(const Key &key) const
        {
            typename rb_tree::iterator it = this->find(key);
            if (it == this->end())
                throw std::out_of_range("pos is out of range");
            return it->second;
        }

        T &operator[](const Key &key)
        {
            typename rb_tree::iterator it = this->find(key);
            if (it == this->end())
                it = this->insert(std::make_pair(key, T())).first;
            return it->second;
        }


        value_compare value_comp() const
        {
            return value_compare();
        }
    };

}

#endif
