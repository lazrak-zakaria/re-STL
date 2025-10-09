

#include <memory>
#include "deque_iterator.hpp"
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

        typedef deque_iterator<T, T *, T &> iterator;

    protected:
        typedef pointer *map_pointer;

    protected:
        iterator start;
        iterator finish;

        map_pointer map;
        size_type map_size;
        size_type _buffer_size = 500; 

        allocator_type deque_allocator;
        std::allocator<value_type *> map_allocator;

    public:
        iterator begin() { return start; }
        iterator end() { return finish; }


        reference front() {
            return *begin();
        }

        reference back(){
            iterator answer = end();
            answer--;
            return *answer;
        }


        void allocate_node()
        {
            return deque_allocator.allocate(_buffer_size);
        }

        void create_map_and_nodes(size_type num_elements)
        {
            size_type num_of_nodes = num_elements / _buffer_size + 1;

            size_type new_map_size = std::max(map_size, num_of_nodes + 6);

            map_pointer new_map = map_allocator.allocate(new_map_size);// 

            //i want my starting point to be in the middle
            map_pointer new_start = new_map + 3; 
            map_pointer new_finish = new_map + new_map_size - 3 - 1;

            map_pointer cur = new_start;
            while (cur != new_finish)
            {
                *cur = allocate_node();
                cur++;
            }

            start.set_node(new_start);
            finish.set_node(new_finish);

            start.cur = start.first;
            finish.cur = finish.first + num_elements % _buffer_size;
        }


        
    };

}
