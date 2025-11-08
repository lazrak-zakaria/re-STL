

#ifndef FT_LST_ITERATOR_HPP
#define FT_LST_ITERATOR_HPP

#include "list.hpp"

namespace ft
{

    template <class T>
    class lst_iterator
    {
    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef long long difference_type;
        typedef T *pointer;
        typedef T &reference;

        typedef ft::lst_node<T> *lst_node_ptr;
        
        lst_node_ptr node;

        lst_iterator() : node(NULL)
        {
        }

        lst_iterator(const lst_node_ptr & n) : node(n)
        {
        }

        lst_iterator &operator++()
        {
            node = node->next;
            return *this;
        }

        lst_iterator &operator--()
        {
            node = node->prev;
            return *this;
        }

        pointer operator->() const
        {
            return &node->key;
        }

        reference operator*() const 
        {
            return node->key;
        }

        lst_iterator operator--(int)
        {
            lst_iterator ans = *this;
            --(*this);
            return ans;
        }

        lst_iterator operator++(int)
        {
            lst_iterator ans = *this;
            ++(*this);
            return ans;
        }

        bool operator==(const lst_iterator &it) const
        {
            return it.node == node;
        }

        bool operator!=(const lst_iterator &it) const
        {
            return it.node != node;
        }

        template <typename U>
        lst_iterator (lst_iterator<U> const &other)
            : node((lst_node_ptr)other.node)
        {
        }
    };

}
#endif
