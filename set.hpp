

#ifndef FT__SET__
#define FT__SET__

#include <memory>
#include "rb_tree.hpp"

namespace ft
{
    template <class T,                      // set::key_type/value_type
              class Compare = std::less<T>, // set::key_compare/value_compare  // later i should implement my own comparison object
              class Alloc = std::allocator<T>>
    class set : public rb_tree<T, Compare, Alloc>
    {

    public:
    
    };

}

#endif