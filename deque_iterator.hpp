

namespace ft
{
    template <class T, class Ref, class Ptr>
    struct deque_iterator
    {

        typedef random_access_iterator_tag iterator_category; 
        typedef T value_type;                                 
        typedef Ptr pointer;                                  
        typedef Ref reference;                                
        typedef unsigned long long size_type;
        typedef long difference_type; 
        typedef T **    map_pointer;
        typedef deque_iterator self;


        T* cur;
        T* first;
        T* last;
        map_pointer node; 
                

    };

} 
