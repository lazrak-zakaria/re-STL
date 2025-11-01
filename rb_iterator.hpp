

#ifndef FT_RB_ITERATOR_HPP
#define FT_RB_ITERATOR_HPP

#include "rb_tree.hpp"

namespace ft
{

    
    template <class T>
    class rb_iterator
    {
    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef const T value_type;
        typedef long long difference_type;
        typedef const T *pointer;
        typedef const T &reference;

        typedef ft::rb_node<T> *rb_node_ptr;

        rb_node_ptr node;
        rb_node_ptr nil;

        rb_iterator() : node(NULL), nil (NULL)
        {}

        rb_iterator(const rb_node_ptr node, rb_node_ptr nil) : node(node), nil(nil)
        {
        }

        rb_iterator &operator++()
        {
            if (node->right != nil)
            {
                rb_node_ptr cur = node->right;
                while (cur->left != nil)
                    cur = cur->left;
                node = cur;
            }
            else
            {
                rb_node_ptr cur = node;
                rb_node_ptr parent = cur->parent;
                if (cur == nil)
                    node = parent;
                else
                {
                    while (parent != nil && parent->right == cur)
                    {
                        cur = parent;
                        parent = parent->parent;
                    }
                    node = parent;
                }
            }
            
            // if (node->parent == nil)
            // std::cout << ")))))))" << node->key << "\n";
            return *this;
        }

        rb_iterator &operator--()
        {
            if (node->left != nil)
            {
                rb_node_ptr cur = node->left;
                while (cur->right != nil)
                    cur = cur->right;
                node = cur;
            }
            else
            {
                rb_node_ptr cur = node;
                rb_node_ptr parent = cur->parent;
                if (cur == nil)
                    node = parent; // i added this for rev iter bcz parent->left == cur alwys true if cur is nil;
                else
                {
                    while (parent != nil && parent->left == cur)
                    {
                        cur = parent;
                        parent = parent->parent;
                    }
                    node = parent;
                }
            }
            return *this;
        }

         pointer operator->()
        {
            return &node->key;
        }

         reference operator*()
        {
            return (const reference)node->key;
        }

        rb_iterator operator--(int)
        {
            rb_iterator ans = *this;
            --(*this);
            return ans;
        }

        rb_iterator operator++(int)
        {
            rb_iterator ans = *this;
            ++(*this);
            return ans;
        }

        bool operator==(const rb_iterator &it) const
        {
            return it.node == node;
        }

        bool operator!=(const rb_iterator &it) const
        {
            return it.node != node;
        }


    };

}
#endif
