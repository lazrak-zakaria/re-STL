

#ifndef FT__RED_BLACK_TREE_HPP
#define FT__RED_BLACK_TREE_HPP

#define RED 1
#define BLACK 0
#define null NULL

typedef bool Color;

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

template <class T>
class rb_tree
{

public:
    typedef rb_node<T> *rb_node_ptr;

    rb_node_ptr root;
    rb_node_ptr nil ;
    bool unique = true;

    rb_tree()
    {
        nil = new rb_node<T>();
        nil->parent = nil;
        nil->left = nil;
        nil->right = nil;
        nil->color = BLACK;
        root = nil ;
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

    void insert( T key)
    {
        rb_node_ptr new_node = create_node(key);
        insert_node(new_node);
    }

    void insert_node(rb_node_ptr node)
    {
        rb_node_ptr parent = nil;
        rb_node_ptr cur = root;

        while (cur != nil)
        {
            parent = cur;
            if (node->key < cur->key)
            {
                cur = cur->left;
            }
            else
            {
                cur = cur->right;
            }
        }

        node->parent = parent;

        if (parent == nil)
            root = node;
        else if (node->key < parent->key)
            parent->left = node;
        else
            parent->right = node;

        balance(node);
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

    int hei()
    {
        int i = 0;
        rb_node_ptr t = root;
        while (t != nil)
        {
            i+=1;
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

    void p(rb_node_ptr  ptr)
    {
        if (ptr == nil) return;

        p(ptr->left);
        std::cout<< ptr->key << "\n";
        p(ptr->right);
    }
};

#endif