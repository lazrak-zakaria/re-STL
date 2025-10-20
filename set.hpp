

#ifndef FT__SET__
#define FT__SET__

#include <memory>
#include "rb_tree.hpp"

namespace ft
{

    template <class K>
    struct SetKeyOfTT
    {
        const K &operator()(const K &key) const
        {
            return key;
        }
    };

    template <class T,                     // set::key_type/value_type
              class Compare = ft::less<T>, // set::key_compare/value_compare  // later i should implement my own comparison object
              class Alloc = std::allocator<T>>
    class set : public rb_tree<const T, const T, SetKeyOfTT<T>, Compare, Alloc>
    {

    public:
    };

    template <class T,                     // set::key_type/value_type
              class Compare = ft::less<T>, // set::key_compare/value_compare  // later i should implement my own comparison object
              class Alloc = std::allocator<T>>
    class multiset : public rb_tree<const T, const T, SetKeyOfTT<T>, Compare, Alloc, false>
    {

    public:
    };


    template <class T, class Compare, class Allocator>
    bool operator==(const set<T, Compare, Allocator> &lhs, const set<T, Compare, Allocator> &rhs)
    {
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Compare, class Allocator>
    bool operator!=(const set<T, Compare, Allocator> &lhs, const set<T, Compare, Allocator> &rhs)
    {
        return !(lhs==rhs);
    }

    template <class T, class Compare, class Allocator>
    bool operator<(const set<T, Compare, Allocator> &lhs, const set<T, Compare, Allocator> &rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Compare, class Allocator>
    bool operator>(const set<T, Compare, Allocator> &lhs, const set<T, Compare, Allocator> &rhs)
    {
        return (rhs < lhs);
    }

    template <class T, class Compare, class Allocator>
    bool operator<=(const set<T, Compare, Allocator> &lhs, const set<T, Compare, Allocator> &rhs)
    {
        return !(lhs > rhs);
    }

    template <class T, class Compare, class Allocator>
    bool operator>=(const set<T, Compare, Allocator> &lhs, const set<T, Compare, Allocator> &rhs)
    {
        return !(lhs < rhs);
    }

}

#endif