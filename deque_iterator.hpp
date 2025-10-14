

namespace ft
{
    template <class T, class Ref, class Ptr>
    struct deque_iterator
    {

        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef Ptr pointer;
        typedef Ref reference;
        typedef unsigned long long size_type;
        typedef long difference_type;
        typedef T **map_pointer;
        typedef deque_iterator self;



        T *cur;
        T *first;
        T *last;
        map_pointer node;

        // how many element can be stored in each node;
        size_type _buffer_size = 500; 

        void set_node(map_pointer new_node)
        {
            node = new_node;
            first = *node;
            last = first + _buffer_size;
        }

        self &operator++()
        {
            ++cur;
            if (cur == last)
            {
                set_node(node + 1);
                cur = first;
            }
            return *this;
        }

        self operator++(int)
        {
            self answer = *this;
            ++(*this);
            return answer;
        }

        self &operator--()
        {
            --cur;
            if (cur == last)
            {
                set_node(node + 1);
                cur = first;
            }
            return *this;
        }

        self operator--(int)
        {
            self answer = *this;
            --(*this);
            return answer;
        }


        self& operator+=(difference_type n)
        {
            difference_type offset = n + (cur - first);

            if (offset >= 0 && offset < difference_type(_buffer_size))
            {
                cur = first + offset;
            }
            else
            {
                difference_type node_offset = 0;
                difference_type bf_sz = difference_type(_buffer_size);
                
                if (offset < 0)
                    node_offset = offset / bf_sz - (offset % bf_sz != 0);
                else
                    node_offset = offset / bf_sz;
                
                set_node(node + node_offset);

                cur = first + (offset - node_offset * bf_sz);
            }
            return *this;
        }


    };

}
