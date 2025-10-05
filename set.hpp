

#ifndef FT__SET__
#define FT__SET__

#include <memory>
#include "rb_tree.hpp";

namespace ft
{
    template <class T,                      // set::key_type/value_type
              class Compare = std::less<T>, // set::key_compare/value_compare  // later i should implement my own comparison object
              class Alloc = std::allocator<T>>
    class set
    {

    public:
        typedef T key_type;
        typedef T value_type;
        typedef Compare key_compare;
        typedef Compare value_compare;
        typedef Alloc allocator_type;

        private:
            typedef rb_tree<T, Compare, Alloc>  rbt_type; 

            rbt_type    rbt;


    };

}

#endif