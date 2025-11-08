
#include <iterator>
#ifndef FT__DEQUE_HPP_ITER__
#define FT__DEQUE_HPP_ITER__
namespace ft
{
    template <class T>
    struct deque_iterator
    {

        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef unsigned long long size_type;
        typedef long difference_type;
        typedef T **map_pointer;
        typedef deque_iterator self;

        map_pointer node;
        T *cur;
        T *first;
        T *last;

        deque_iterator() : node(0), cur(0), first(0), last(0)
        {
        }
        // how many byte in each node;

        size_t deque_buf_size(size_t sz) const
        {
            size_type _buffer_size = 4096;
            // i return how many elements can be stored
            return sz < _buffer_size ? size_t(_buffer_size / sz) : size_t(1);
        }
        size_t buffer_size() const
        {
            return deque_buf_size(sizeof(T));
        }

        void set_node(map_pointer new_node)
        {
            node = new_node;
            first = *node;
            last = first + difference_type(buffer_size());
        }

        reference operator*() const
        {
            return *cur;
        }
        pointer operator->() const
        {
            return &(operator*());
        }
        difference_type operator-(const deque_iterator &other) const
        {
            return difference_type(buffer_size()) * (node - other.node) + (cur - first) - (other.cur - other.first);
        }

        deque_iterator &operator++()
        {
            ++cur;
            if (cur == last)
            {
                set_node(node + 1);
                cur = first;
            }
            return *this;
        }

        deque_iterator operator++(int)
        {
            deque_iterator answer = *this;
            ++(*this);
            return answer;
        }

        deque_iterator &operator--()
        {
            if (cur == first)
            {
                set_node(node - 1);
                cur = last;
            }
            --cur;
            return *this;
        }

        deque_iterator operator--(int)
        {
            deque_iterator answer = *this;
            --(*this);
            return answer;
        }

        deque_iterator &operator+=(difference_type n)
        {
            difference_type offset = n + (cur - first);
            difference_type bf_sz = difference_type(buffer_size());
            if (offset >= 0 && offset < bf_sz)
            {
                cur = first + offset;
            }
            else
            {
                difference_type node_offset = 0;

                if (offset < 0)
                    node_offset = offset / bf_sz - (offset % bf_sz != 0);
                else
                    node_offset = offset / bf_sz;

                set_node(node + node_offset);

                cur = first + (offset - node_offset * bf_sz);
            }
            return *this;
        }

        deque_iterator &operator-=(difference_type n)
        {
            return operator+=(-n);
        }

        deque_iterator operator+(difference_type n) const
        {
            deque_iterator tmp = *this;
            return tmp += n;
        }

        deque_iterator operator-(difference_type n) const
        {
            deque_iterator tmp = *this;
            return tmp -= n;
        }

        reference operator[](difference_type n) const
        {
            return *(*this + n);
        }

        bool operator==(const self &rhs) const
        {
            return cur == rhs.cur;
        }

        bool operator!=(const self &rhs) const
        {
            return cur != rhs.cur;
        }

        bool operator<(const self &rhs) const
        {
            return (node == rhs.node) ? (cur < rhs.cur) : (node < rhs.node);
        }
        bool operator>(const self &rhs) const
        {
            return !(*this < rhs) && !(*this == rhs);
        }

        bool operator>=(const self &rhs) const
        {
            return !(*this < rhs);
        }

        bool operator<=(const self &rhs) const
        {
            return !(*this > rhs);
        }

        template <typename U>
        deque_iterator(deque_iterator<U> const &other)
            : node((map_pointer)other.node),

              cur((pointer)other.cur),
              first((pointer)other.first),
              last((pointer)other.last)
        {
        }
    };

}
#endif