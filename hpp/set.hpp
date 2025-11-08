

#ifndef FT__SET__
#define FT__SET__

#include <memory>
#include "rb_tree.hpp"
#include "functional.hpp"
namespace ft
{
    template <class T,                     // set::key_type/value_type
              class Compare = ft::less<T>, // set::key_compare/value_compare  // later i should implement my own comparison object
              class Alloc = std::allocator<T> >
    class set : public rb_tree< T,  T, ft::SetKeyOfT<T>, Compare, Alloc>
    {
        typedef ft::rb_tree<  T,  T, ft::SetKeyOfT<T>, Compare, Alloc> rb_tree;

    public:

        explicit set(const Compare &comp = Compare(), const Alloc &a = Alloc()) : rb_tree(comp, a)
        {
        }

        template <class InputIt>
        set(InputIt first, InputIt last,
            const Compare &comp = Compare(), const Alloc &alloc = Alloc(),
            typename ft::enable_if<!ft::is_integral<InputIt>::value>::type * = 0) : rb_tree(first,
                                                                                            last,
                                                                                            comp,
                                                                                            alloc)
        {
        }

        set(const set &other) : rb_tree(other)
        {
        }
            ~set()
            {
                
            }

    };

    template <class T,                     // set::key_type/value_type
              class Compare = ft::less<T>, // set::key_compare/value_compare  // later i should implement my own comparison object
              class Alloc = std::allocator<T> >
    class multiset : public rb_tree< T,  T, SetKeyOfT<T>, Compare, Alloc, false>
    {
        typedef ft::rb_tree<  T,  T, SetKeyOfT<T>, Compare, Alloc, false> rb_tree;

    public:


    explicit multiset(const Compare &comp = Compare(), const Alloc &a = Alloc()) : rb_tree(comp, a)
    {
    }

    template <class InputIt>
    multiset(InputIt first, InputIt last,
        const Compare &comp = Compare(), const Alloc &alloc = Alloc(),
        typename ft::enable_if<!ft::is_integral<InputIt>::value>::type * = 0) : rb_tree(first,
                                                                                        last,
                                                                                        comp,
                                                                                        alloc)
    {
    }

    multiset(const multiset &other) : rb_tree(other)
    {
    }


    ~multiset()
    {

    }

    };

    template <class T, class Compare, class Allocator>
    bool operator==(const set<T, Compare, Allocator> &lhs, const set<T, Compare, Allocator> &rhs)
    {
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Compare, class Allocator>
    bool operator!=(const set<T, Compare, Allocator> &lhs, const set<T, Compare, Allocator> &rhs)
    {
        return !(lhs == rhs);
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

    template <class T, class Compare, class Allocator>
    bool operator==(const multiset<T, Compare, Allocator> &lhs, const multiset<T, Compare, Allocator> &rhs)
    {
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Compare, class Allocator>
    bool operator!=(const multiset<T, Compare, Allocator> &lhs, const multiset<T, Compare, Allocator> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Compare, class Allocator>
    bool operator<(const multiset<T, Compare, Allocator> &lhs, const multiset<T, Compare, Allocator> &rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Compare, class Allocator>
    bool operator>(const multiset<T, Compare, Allocator> &lhs, const multiset<T, Compare, Allocator> &rhs)
    {
        return (rhs < lhs);
    }

    template <class T, class Compare, class Allocator>
    bool operator<=(const multiset<T, Compare, Allocator> &lhs, const multiset<T, Compare, Allocator> &rhs)
    {
        return !(lhs > rhs);
    }

    template <class T, class Compare, class Allocator>
    bool operator>=(const multiset<T, Compare, Allocator> &lhs, const multiset<T, Compare, Allocator> &rhs)
    {
        return !(lhs < rhs);
    }

    template <class Key, class Compare, class Alloc>
    void swap(ft::set<Key,  Compare, Alloc> &lhs,
              ft::set<Key,  Compare, Alloc> &rhs)
    {
        lhs.swap(rhs);
    }
    template <class Key, class Compare, class Alloc>
    void swap(ft::multiset<Key, Compare, Alloc> &lhs,
              ft::multiset<Key, Compare, Alloc> &rhs)
    {
        lhs.swap(rhs);
    }

}

#endif