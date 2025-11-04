

#ifndef FT_MAP_hpp__
#define FT_MAP_hpp__
#include <memory>
#include "rb_tree.hpp"
// #include "stdexcept.hpp"
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
              class Alloc = std::allocator<ft::pair< Key, T> > >
    class map : public ft::rb_tree<ft::pair< const Key, T>, Key, MapKeyOfT<ft::pair< const Key, T> >, Compare, Alloc>
    {
        typedef ft::rb_tree<ft::pair< const Key, T>, Key, MapKeyOfT<ft::pair< const Key, T> >, Compare, Alloc> rb_tree;

    public:
        typedef T mapped_type; //            = T;

        explicit map(const Compare &comp = Compare(), const Alloc &a = Alloc()) : rb_tree(comp, a)
        {
        }

        template <class InputIt>
        map(InputIt first, InputIt last,
            const Compare &comp = Compare(), const Alloc &alloc = Alloc(),
            typename ft::enable_if<!ft::is_integral<InputIt>::value>::type * = 0) : rb_tree(first,
                                                                                            last,
                                                                                            comp,
                                                                                            alloc)
        {
        }

        map(const map &other) : rb_tree(other)
        {
        }
        ~map()
        {

        }
        class value_compare
        {
        protected:
            Compare comp;
            value_compare(Compare c)
                : comp(c)
            {
            }

        public:
            bool operator()(const typename rb_tree::value_type &x, const typename rb_tree::value_type &y) const
            {
                return comp(x.first, y.first);
            }
        };

        T &at(const Key &key)
        {
            typename rb_tree::iterator it = this->find(key);
            if (it == this->end())
                throw ft::out_of_range("not found");
            return it->second;
        }

        const T &at(const Key &key) const
        {
            typename rb_tree::iterator it = this->find(key);
            if (it == this->end())
                throw ft::out_of_range("pos is out of range");
            return it->second;
        }

        T &operator[](const Key &key)
        {
            typename rb_tree::iterator it = this->find(key);
            if (it == this->end())
                it = this->insert(ft::make_pair(key, T())).first;
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
              class Alloc = std::allocator<std::pair< Key, T> > >
    class multimap : public ft::rb_tree<ft::pair< const Key, T>, Key, MapKeyOfT<ft::pair< const Key, T> >, Compare, Alloc, false>
    {
        typedef ft::rb_tree<ft::pair< const Key, T>, Key, MapKeyOfT<ft::pair< const Key, T> >, Compare, Alloc, false> rb_tree;

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
            bool operator()(const typename rb_tree::value_type &x, const typename rb_tree::value_type &y) const
            {
                return comp(x.first, y.first);
            }
        };

        T &at(const Key &key)
        {
            typename rb_tree::iterator it = this->find(key);
            if (it == this->end())
                throw ft::out_of_range("not found");
            return it->second;
        }

        const T &at(const Key &key) const
        {
            typename rb_tree::iterator it = this->find(key);
            if (it == this->end())
                throw ft::out_of_range("pos is out of range");
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

    template <class T, class Compare, class Allocator>
    bool operator==(const map<T, Compare, Allocator> &lhs, const map<T, Compare, Allocator> &rhs)
    {
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Compare, class Allocator>
    bool operator!=(const map<T, Compare, Allocator> &lhs, const map<T, Compare, Allocator> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Compare, class Allocator>
    bool operator<(const map<T, Compare, Allocator> &lhs, const map<T, Compare, Allocator> &rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Compare, class Allocator>
    bool operator>(const map<T, Compare, Allocator> &lhs, const map<T, Compare, Allocator> &rhs)
    {
        return (rhs < lhs);
    }

    template <class T, class Compare, class Allocator>
    bool operator<=(const map<T, Compare, Allocator> &lhs, const map<T, Compare, Allocator> &rhs)
    {
        return !(lhs > rhs);
    }

    template <class T, class Compare, class Allocator>
    bool operator>=(const map<T, Compare, Allocator> &lhs, const map<T, Compare, Allocator> &rhs)
    {
        return !(lhs < rhs);
    }

    template <class T, class Compare, class Allocator>
    bool operator==(const multimap<T, Compare, Allocator> &lhs, const multimap<T, Compare, Allocator> &rhs)
    {
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Compare, class Allocator>
    bool operator!=(const multimap<T, Compare, Allocator> &lhs, const multimap<T, Compare, Allocator> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Compare, class Allocator>
    bool operator<(const multimap<T, Compare, Allocator> &lhs, const multimap<T, Compare, Allocator> &rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Compare, class Allocator>
    bool operator>(const multimap<T, Compare, Allocator> &lhs, const multimap<T, Compare, Allocator> &rhs)
    {
        return (rhs < lhs);
    }

    template <class T, class Compare, class Allocator>
    bool operator<=(const multimap<T, Compare, Allocator> &lhs, const multimap<T, Compare, Allocator> &rhs)
    {
        return !(lhs > rhs);
    }

    template <class T, class Compare, class Allocator>
    bool operator>=(const multimap<T, Compare, Allocator> &lhs, const multimap<T, Compare, Allocator> &rhs)
    {
        return !(lhs < rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    void swap(ft::map<Key, T, Compare, Alloc> &lhs,
              ft::map<Key, T, Compare, Alloc> &rhs)
    {
        lhs.swap(rhs);
    }
    template <class Key, class T, class Compare, class Alloc>
    void swap(ft::multimap<Key, T, Compare, Alloc> &lhs,
              ft::multimap<Key, T, Compare, Alloc> &rhs)
    {
        lhs.swap(rhs);
    }
}

#endif
