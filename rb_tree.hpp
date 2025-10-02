

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
        T data;
        Color color;

        RBTreeNode(const T &data)
            : data(data), left(nullptr), right(nullptr), parent(nullptr), color(RED)
        {
        }
};


template<class T>
class rb_tree 
{
    public:
        rb_node* root;
    

    void rotate_left(rb_node * x)
    {
        rb_node * y = x.right

        x.right = y.left;

        if (y.left)
            y.left.parent = x;
        y.parent = x.parent


        if (x == root)
            root = y;
        else if (y.parent.left == x)
            y.parent.left = y;
        else
            y.parent.right = y;


        y.left = x;
        x.parent = y;
    }

    void rotate_right(rb_node * y)
    {
        rb_node* x = y.left;


        y.left = x.right;


        if (x.right)
            x.right.parent = y;
        x.parent = y.parent;
        

        if (root == y)
            root = x;
        else if (y.parent.left == y)
            y.parent.left = x;
        else
            y.parent.right = x;

        x.right = y;
        y.parent = x;        
    }

};


#endif