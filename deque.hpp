

#include <memory>

namespace ft
{

    template <

        class T,
        class Allocator = std::allocator<T>>
    class deque

    {

    public:
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef typename allocator_traits<Allocator>::pointer pointer;
        typedef typename allocator_traits<Allocator>::const_pointer const_pointer;
        typedef value_type &reference;
        typedef const value_type &const_reference;

        typedef unsigned long size_type;


    protected:
        typedef pointer* map_pointer;

    
    protected:
        map_pointer map;
        size_type map_size;

    public:
        template <class InputIterator>
        void assign(InputIterator first, InputIterator last);
        void assign(size_type n, const value_type &val);



        iterator insert(iterator position, const value_type &val);
        void insert(iterator position, size_type n, const value_type &val);
        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last);


        iterator erase (iterator position);iterator erase (iterator first, iterator last);


        void resize (size_type n, value_type val = value_type());
    };

}
