

#ifndef FT__RED_BLACK_TREE_HPP
#define FT__RED_BLACK_TREE_HPP

#define RED 1
#define BLACK 0
#define null NULL

typedef bool Color;

#include <memory>

namespace ft
{

    template <class T>
    class rb_node
    {
    public:
        rb_node *parent;
        rb_node *left;
        rb_node *right;
        T key;
        Color color;

        rb_node(const T &key)
            : key(key), left(nullptr), right(nullptr), parent(nullptr), color(RED)
        {
        }
        rb_node()
            : left(nullptr), right(nullptr), parent(nullptr), color(RED)
        {
        }
    };

#include "rb_iterator.hpp"
#include "utility.hpp"

    template <class T,
              class Compare = std::less<T>, // set::key_compare/value_compare  // later i should implement my own comparison object
              class Alloc = std::allocator<T>,
              bool Unique = true>
    class rb_tree
    {

    public:
        typedef T key_type;
        typedef T value_type;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef Alloc allocator_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
        typedef Compare key_compare;

        typedef ft::rb_iterator<T> iterator;

    private:
    public:
        typedef rb_node<T> *rb_node_ptr;

        rb_node_ptr root;
        rb_node_ptr nil;

        key_compare cmp;
        bool unique = Unique;

        rb_tree()
        {
            nil = new rb_node<T>();
            nil->parent = nil;
            nil->left = nil;
            nil->right = nil;
            nil->color = BLACK;
            root = nil;
            cmp = key_compare();
        }

        rb_node_ptr create_node(T key)
        {
            rb_node_ptr node = new rb_node<T>();
            node->key = key;
            node->color = RED;
            node->left = nil;
            node->right = nil;
            node->parent = nil;
            return node;
        }

        void rotate_left(rb_node_ptr x)
        {
            rb_node_ptr y = x->right;

            x->right = y->left;

            if (y->left)
                y->left->parent = x;

            y->parent = x->parent;

            if (x == root)
                root = y;
            else if (y->parent->left == x)
                y->parent->left = y;
            else
                y->parent->right = y;

            y->left = x;
            x->parent = y;
        }

        void rotate_right(rb_node_ptr y)
        {
            rb_node_ptr x = y->left;

            y->left = x->right;

            if (x->right)
                x->right->parent = y;

            x->parent = y->parent;

            if (root == y)
                root = x;
            else if (y->parent->left == y)
                y->parent->left = x;
            else
                y->parent->right = x;

            x->right = y;
            y->parent = x;
        }

        void insert(T key)
        {
            rb_node_ptr new_node = create_node(key);
            insert_node(new_node);
        }

        ft::pair<rb_node_ptr, bool> insert_node(rb_node_ptr node)
        {
            rb_node_ptr parent = nil;
            rb_node_ptr cur = root;

            while (cur != nil)
            {
                parent = cur;
                if (node->key == cur->key && unique)
                    return ft::make_pair(cur, false);

                if (node->key < cur->key)
                    cur = cur->left;
                else
                    cur = cur->right;
            }

            node->parent = parent;

            if (parent == nil)
                root = node;
            else if (node->key < parent->key)
                parent->left = node;
            else
                parent->right = node;

            balance(node);
            return ft::make_pair(node, true);
        }

        void balance(rb_node_ptr cur)
        {

            while (cur->parent->color == RED)
            {
                rb_node_ptr parent = cur->parent;
                rb_node_ptr g_parent = parent->parent;

                if (parent == g_parent->left)
                {
                    rb_node_ptr uncle = g_parent->right;

                    if (uncle->color == RED)
                    {
                        parent->color = BLACK;
                        uncle->color = BLACK;
                        g_parent->color = RED;
                        cur = g_parent;
                    }
                    else
                    {
                        if (cur == parent->right)
                        {
                            cur = parent;
                            rotate_left(cur);
                        }
                        parent = cur->parent;
                        g_parent = parent->parent;
                        uncle = g_parent->right;

                        parent->color = BLACK;
                        g_parent->color = RED;

                        rotate_right(g_parent);
                    }
                }
                else
                {
                    rb_node_ptr uncle = g_parent->left;

                    if (uncle->color == RED)
                    {
                        parent->color = BLACK;
                        uncle->color = BLACK;
                        g_parent->color = RED;
                        cur = g_parent;
                    }
                    else
                    {
                        if (cur == parent->left)
                        {
                            cur = parent;
                            rotate_right(cur);
                        }
                        parent = cur->parent;
                        g_parent = parent->parent;
                        uncle = g_parent->left;

                        parent->color = BLACK;
                        g_parent->color = RED;

                        rotate_left(g_parent);
                    }
                }
            }
            this->root->color = BLACK;
        }

        rb_node_ptr rb_minimum(rb_node_ptr node)
        {
            while (node != nil)
                node = node->left;
            return node;
        }

        rb_node_ptr find(const value_type &key)
        {
            rb_node_ptr head = root;
            while (head != nil)
            {
                if (head->key == key)
                    return head;
                else if (key < head->key)
                    head = head->left;
                else
                    head = head->right;
            }
            return nil;
        }

        void transplant(rb_node_ptr first, rb_node_ptr second)
        {
            if (first->parent == nil)
                root = second;
            else if (first == first->parent->left)
                first->parent->left = second;
            else
                first->parent->right = second;
            void

                second->parent = first->parent;
        }

        bool delete_node(T key)
        {
            rb_node_ptr to_delete = find(key);
            if (to_delete == nil)
                return false;

            rb_node_ptr y = to_delete;
            Color y_color = to_delete->color;

            rb_node_ptr fix = nil;
            if (to_delete->left == nil)
            {
                fix = to_delete->right;
                transplant(to_delete, to_delete->right);
            }
            else if (to_delete->right == nil)
            {
                fix = to_delete->left;
                transplant(to_delete, to_delete->left);
            }
            else
            {
                y = rb_minimum(to_delete->right);
                y_color = y->color;

                fix = y->right;
                if (y->parent == to_delete)
                    fix->parent = y;
                else
                {
                    transplant(y, y->right);
                    y->right = to_delete->right;
                    y->right->parent = y;
                }
                transplant(to_delete, y);
                y->left = to_delete->left;
                y->left->parent = y;
                y->color = to_delete->color;
            }
            if (y_color == BLACK)
                delete_fixup(fix);
            return true;
        }

        void delete_fixup(rb_node_ptr x)
        {
            while (x != root && x->color == BLACK)
            {
                if (x == x->parent->left)
                {

                    rb_node_ptr w = x->parent->right;
                    if (w->color == RED)
                    {
                        w->color = BLACK;
                        x->parent->color = RED;
                        rotate_left(x->parent);
                        w = x->parent->right;
                    }
                    if (w->left->color == BLACK && w->right->color == BLACK)
                    {
                        w->color = RED;
                        x = x->parent;
                    }
                    else
                    {
                        if (w->right->color == BLACK)
                        {
                            w->left->color = BLACK;
                            w->color = RED;
                            rotate_right(w);
                            w = x->parent->right;
                        }

                        w->color = x->parent->color;
                        x->parent->color = BLACK;
                        w->right->color = BLACK;
                        rotate_left(x->parent);
                        x = root;
                    }
                }
                else
                {
                    rb_node_ptr w = x->parent->left;
                    if (w->color == RED)
                    {
                        w->color = BLACK;
                        x->parent->color = RED;
                        rotate_right(x->parent);
                        w = x->parent->left;
                    }
                    if (w->right->color == BLACK && w->left->color == BLACK)
                    {
                        w->color = RED;
                        x = x->parent;
                    }
                    else
                    {
                        if (w->left->color == BLACK)
                        {
                            w->right->color = BLACK;
                            w->color = RED;
                            rotate_left(w);
                            w = x->parent->left;
                        }
                        w->color = x->parent->color;
                        x->parent->color = BLACK;
                        w->left->color = BLACK;
                        rotate_right(x->parent);
                        x = root;
                    }
                }
            }
            x->color = BLACK;
        }

        void clear(rb_node_ptr node)
        {
            if (node == nil)
                return;

            clear(node->left);
            clear(node->right);

            delete node;
        }

        int hei()
        {
            int i = 0;
            rb_node_ptr t = root;
            while (t != nil)
            {
                i += 1;
                t = t->right;
                /* code */
            }
            return i;
        }

        void print()
        {
            // std::cout << "print\n";
            p(root);
        }

        void p(rb_node_ptr ptr)
        {
            if (ptr == nil)
                return;

            p(ptr->left);
            std::cout << ptr->key << "\n";
            p(ptr->right);
        }

    public:
        iterator lower_bound(const value_type &val) const
        {
            rb_node_ptr cur = root;
            rb_node_ptr ans = nil;
            while (cur != nil)
            {
                if (val == cur->key)
                    return iterator(cur);
                else if (val < cur->key)
                {
                    ans = cur;
                    cur = cur->left;
                }
                else
                    cur = cur->right;
            }
            return iterator(ans);
        }

        iterator upper_bound(const value_type &val) const
        {
            rb_node_ptr cur = root;
            rb_node_ptr ans = nil;
            while (cur != nil)
            {
                if (val < cur->key)
                {
                    ans = cur;
                    cur = cur->left;
                }
                else
                    cur = cur->right;
            }
            return iterator(ans);
        }

    private:
        size_type count(const value_type &val, rb_node_ptr node) const
        {
            if (node == nil)
                return 0;

            if (val < node->key)
                return count(val, node->left);
            else if (val > node->key)
                return count(val, node->right);
            else
            {
                if (unique)
                    return 1;
                return 1 + count(val, node->left) + count(val, node->right);
            }
        }

    public:
        size_type count(const value_type &val)
        {
            return count(val, root);
        }

        iterator find_(const value_type &val) const
        {
            return iterator(find(val));
        }

        pair<iterator, iterator> equal_range(const value_type &val) const
        {
            return ft::make_pair(lower_bound(val), upper_bound(val));
        }
    };

}

#endif