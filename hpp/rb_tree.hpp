

#ifndef FT__RED_BLACK_TREE_HPP
#define FT__RED_BLACK_TREE_HPP

#define RED 1
#define BLACK 0
#define null NULL
#include <iostream>
typedef bool Color;

#include <memory>
#include "iterator.hpp"
#include "functional.hpp"
#include "algorithm.hpp"
#include "utility.hpp"
#include "iterator.hpp"
namespace ft
{

    template <class Key>
    class rb_node
    {
    public:
        Key key;
        rb_node *parent;
        rb_node *left;
        rb_node *right;
        Color color;

        rb_node(const Key &key)
            : key(key), parent(NULL), left(NULL), right(NULL), color(RED)
        {
        }
        rb_node()
            : left(NULL), right(NULL), parent(NULL), color(RED)
        {
        }
        ~rb_node()
        {

        }
    };
}

// #include "rb_iterator.hpp"

namespace ft
{
    template <class Key,
              class Ky,
              class KeyType,
              class Compare = ft::less<Key>, // set::key_compare/value_compare  // later i should implement my own comparison object
              class Alloc = std::allocator<Key>,
              bool Unique = true>
    class rb_tree
    {

    private:
        template <class T>
        class rb_iterator
        {
        public:
            friend class rb_tree;
            typedef std::bidirectional_iterator_tag iterator_category;
            typedef const T value_type;
            typedef long difference_type;
            typedef T *pointer;
            typedef const T &reference;

        private:
            typedef ft::rb_node<T> *rb_node_ptr;
            rb_node_ptr node;
            rb_node_ptr nil;

        public:
            rb_iterator() : node(NULL), nil(NULL)
            {
            }

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
                return node->key;
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

    public:
        typedef Ky key_type;
        typedef Key value_type;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef Alloc allocator_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef typename Alloc::pointer pointer;
        typedef typename Alloc::const_pointer const_pointer;
        typedef Compare key_compare;
        typedef rb_iterator<Key> iterator;
        typedef rb_iterator<Key> const_iterator;
        typedef ft::reverse_iterator_<iterator> reverse_iterator;
        typedef ft::reverse_iterator_<const_iterator> const_reverse_iterator;

    private:
        typedef KeyType key_of_type;
        typedef rb_node<Key> *rb_node_ptr;

        rb_node_ptr root;
        rb_node_ptr nil;

        key_compare cmp;
        bool unique;
        size_type _size;
        typename allocator_type::template rebind<ft::rb_node<value_type> >::other alloc;

    public:
        explicit rb_tree(const key_compare &comp = key_compare(), const allocator_type &a = allocator_type()) : cmp(comp), alloc(a)
        {
            initialize();
        }

        void initialize()
        {
            unique = Unique;
            nil = alloc.allocate(1);
            alloc.construct(nil, value_type());
            nil->parent = nil;
            nil->left = nil;
            nil->right = nil;
            nil->color = BLACK;
            root = nil;
            _size = 0;
        }

        template <class InputIterator>
        rb_tree(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
                const allocator_type &alloc = allocator_type())
            : cmp(comp), alloc(alloc)
        {
            initialize();
            while (first != last)
            {
                insert(*first);
                ++first;
            }
        }

        rb_tree(const rb_tree &x) : cmp(x.cmp), alloc(x.alloc)
        {
            initialize();
            *this = x;
        }

        void update_nil_parent()
        {
            if (root == nil)
                nil->parent = nil;
            else
                nil->parent = rb_maximum(root);
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

        value_compare value_comp() const
        {
            return value_compare();
        }

    private:
        rb_node_ptr create_node(Key key)
        {

            rb_node_ptr node = alloc.allocate(1);
            alloc.construct(node, key);
            node->color = RED;
            node->left = nil;
            node->right = nil;
            node->parent = nil;
            return node;
        }

        void deallocate_node(rb_node_ptr node)
        {
            // try
            // {

            alloc.destroy(node);
            std::cerr << "ZZZZ\n";
            alloc.deallocate(node, 1);
            // catch (const std::bad_alloc& e) {
            //     std::cerr << "Memory HHHHHHHHHHHHHHHHHHHHHHHHHHHHH failed: \n" << e.what() << std::endl;
            //     // Handle the error gracefully

            // }
        }

        void rotate_left(rb_node_ptr x)
        {
            rb_node_ptr y = x->right;

            x->right = y->left;

            if (y->left != nil)
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

            if (x->right != nil)
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

        const Ky &get_kot(rb_node_ptr node) const
        {
            return key_of_type()(node->key);
        }

        ft::pair<rb_node_ptr, bool> insert_node(rb_node_ptr node)
        {
            // std::cerr << node->key << "<%%%%%%%%%\n";
            rb_node_ptr parent = nil;
            rb_node_ptr cur = root;
            while (cur != nil)
            {
                parent = cur;
                // cmpare here i think its ok as compare pair with pair; wont need kot
                if (!cmp(get_kot(node), get_kot(cur)) && !cmp(get_kot(cur), get_kot(node)) && unique)
                    return ft::make_pair(cur, false);

                if (cmp(get_kot(node), get_kot(cur)))
                    cur = cur->left;
                else
                    cur = cur->right;
            }
            node->parent = parent;

            if (parent == nil)
            {
                root = node;
            }
            else if (cmp(get_kot(node), get_kot(parent)))
                parent->left = node;
            else
                parent->right = node;

            balance(node);
            update_nil_parent();
            return ft::make_pair(node, true);
        }

        void balance(rb_node_ptr cur)
        {

            while (cur->parent->color == RED)
            {

                rb_node_ptr parent = cur->parent;
                rb_node_ptr g_parent = parent->parent;

                // std::cout << nil << "   " << cur->color << "\n";
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

        rb_node_ptr rb_minimum(rb_node_ptr node) const
        {
            while (node->left != nil)
                node = node->left;
            return node;
        }
        rb_node_ptr rb_maximum(rb_node_ptr node) const
        {
            while (node->right != nil)
                node = node->right;
            return node;
        }

        rb_node_ptr find_(const Ky &key) const
        {
            rb_node_ptr cur = root;
            while (cur != nil)
            {
                if (!cmp(key, get_kot(cur)) && !cmp(get_kot(cur), key))
                    return cur;
                else if (cmp(key, get_kot(cur)))
                    cur = cur->left;
                else
                    cur = cur->right;
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

            second->parent = first->parent;
        }

        bool delete_node(rb_node_ptr to_delete)
        {
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
            update_nil_parent();
            deallocate_node(to_delete); // :)
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

            deallocate_node(node);
        }

    public:
        ~rb_tree()
        {

            clear();
            deallocate_node(root);
        }

        iterator lower_bound(const Ky &val)
        {

            rb_node_ptr cur = root;
            rb_node_ptr ans = nil;

            while (cur != nil)
            {
                if (!cmp(val, get_kot(cur)) && !cmp(get_kot(cur), val))
                {
                    if (unique)
                        return iterator(cur, nil);

                    else
                    {
                        ans = cur;
                        cur = cur->left;
                    }
                }
                else if (cmp(val, get_kot(cur)))
                {
                    ans = cur;
                    cur = cur->left;
                }
                else
                    cur = cur->right;
            }
            return iterator(ans, nil);
        }

        const_iterator lower_bound(const Ky &val) const
        {

            rb_node_ptr cur = root;
            rb_node_ptr ans = nil;

            while (cur != nil)
            {
                if (!cmp(val, get_kot(cur)) && !cmp(get_kot(cur), val))
                {
                    if (unique)
                        return const_iterator(cur, nil);
                    else
                    {
                        ans = cur;
                        cur = cur->left;
                    }
                }
                else if (cmp(val, get_kot(cur)))
                {
                    ans = cur;
                    cur = cur->left;
                }
                else
                    cur = cur->right;
            }
            return const_iterator(ans, nil);
        }

        iterator upper_bound(const Ky &val)
        {
            rb_node_ptr cur = root;
            rb_node_ptr ans = nil;
            while (cur != nil)
            {
                if (cmp(val, get_kot(cur)))
                {
                    ans = cur;
                    cur = cur->left;
                }
                else
                    cur = cur->right;
            }
            return iterator(ans, nil);
        }
        const_iterator upper_bound(const Ky &val) const
        {
            rb_node_ptr cur = root;
            rb_node_ptr ans = nil;
            while (cur != nil)
            {
                if (cmp(val, get_kot(cur)))
                {
                    ans = cur;
                    cur = cur->left;
                }
                else
                    cur = cur->right;
            }
            return const_iterator(ans, nil);
        }

    private:
        size_type count(const Ky &val, rb_node_ptr node) const
        {
            if (node == nil)
                return 0;

            if (!cmp(val, get_kot(node)) && !cmp(get_kot(node), val))
            {
                if (unique)
                    return 1;
                return 1 + count(val, node->left) + count(val, node->right);
            }

            if (cmp(val, get_kot(node)))
                return count(val, node->left);
            else
                return count(val, node->right);
        }

    public:
        size_type count(const Ky &val)
        {
            return count(val, root);
        }

        iterator find(const Ky &val)
        {
            return iterator(find_(val), nil);
        }
        const_iterator find(const Ky &val) const
        {
            return const_iterator(find_(val), nil);
        }

        pair<iterator, iterator> equal_range(const Ky &val)
        {
            return ft::make_pair(lower_bound(val), upper_bound(val));
        }

        pair<const_iterator, const_iterator> equal_range(const Ky &val) const
        {
            return ft::make_pair(lower_bound(val), upper_bound(val));
        }

        iterator begin()
        {
            rb_node_ptr b = rb_minimum(root);
            return iterator(b, nil);
        }
        iterator end()
        {
            rb_maximum(root);
            return iterator(nil, nil);
        }

        const_iterator begin() const
        {
            rb_node_ptr b = rb_minimum(root);
            return const_iterator(b, nil);
        }
        const_iterator end() const
        {
            rb_maximum(root);
            return const_iterator(nil, nil);
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }

        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end());
        }
        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(begin());
        }

        size_type size() const
        {
            return _size;
        }

        bool empty() const
        {
            return !_size;
        }

        // Modifier:
        ft::pair<iterator, bool> insert(const value_type &val)
        {
            rb_node_ptr new_node = create_node(val);
            ft::pair<rb_node_ptr, bool> is_inserted = insert_node(new_node);
            if (!is_inserted.second)
                deallocate_node(new_node);//hehehehe
            _size += is_inserted.second;
            ft::pair<iterator, bool> ans = ft::make_pair(iterator(is_inserted.first, nil), is_inserted.second);

            return ans;
        }

    private:
        iterator insert_(iterator position, const value_type &val)
        {
            (void)position;
            ft::pair<iterator, bool> ans = insert(val);
            return ans.first;
        }

        template <class InputIterator>
        void insert_(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
        {
            while (first != last)
            {
                insert(*first);
                first++;
            }
        }

    public:
        iterator insert(iterator position, const value_type &val)
        {
            return insert_(position, val);
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            insert_(first, last);
        }

        void erase(iterator position)
        {
            _size -= delete_node(position.node); // i need to make rb_tree friend to iter
        }

        size_type erase(const Ky &val)
        {
            size_type old_size = _size;
            while (true)
            {
                rb_node_ptr to_delete = find_(val);
                _size -= delete_node(to_delete);
                if (to_delete == nil)
                    break;
            }
            return old_size - _size;
        }

        void erase(iterator first, iterator last)
        {
            while (first != last)
            {
                iterator it = first;
                ++first;
                _size -= delete_node(it.node);
            }
        }

        void clear()
        {
            clear(root);
            _size = 0;
            root = nil;
        }

        void swap(rb_tree &other)
        {
            ft::swap(root, other.root);
            ft::swap(nil, other.nil);
            ft::swap(cmp, other.cmp);
            ft::swap(_size, other._size);
            ft::swap(alloc, other.alloc);   //
            ft::swap(unique, other.unique); //
        }

        allocator_type get_allocator() const
        {
            return allocator_type();
        }

        key_compare key_comp() const
        {
            return cmp;
        }

        size_type max_size() const
        {
            return size_type(-1);
        }

        rb_tree &operator=(const rb_tree &x)
        {
            if (this == &x)
            {
                return *this;
            }

            clear();
            iterator it = x.begin();
            iterator it_end = x.end();
            cmp = x.cmp;
            alloc = x.alloc;
            while (it != it_end)
            {
                insert(*it);
                ++it;
            }
            return *this;
        }
    };


}

#endif