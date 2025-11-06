

#include <memory>
#include "deque_iterator.hpp"
#include "reverse_iterator.hpp"
#include "iterator_traits.hpp"
#include "algorithm.hpp"
#include <algorithm>
#include <exception>
#include <iostream>
#include "stdexcept.hpp"
#define h std::cout << "here\n"
#define g(x) std::cout << "here: " << x << "\n"

namespace ft
{

    template <
        class T,
        class Allocator = std::allocator<T> >
    class deque
    {

    public:
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
        typedef value_type &reference;
        typedef const value_type &const_reference;

        typedef unsigned long size_type;
        typedef long difference_type;
        typedef deque_iterator<T> iterator;
        typedef deque_iterator<const T> const_iterator;
        typedef ft::reverse_iterator_<iterator> reverse_iterator;
        typedef ft::reverse_iterator_<const_iterator> const_reverse_iterator;

    protected:
        typedef pointer *map_pointer;

    protected:
        iterator start;
        iterator finish;

        map_pointer map;
        size_type map_size;
        allocator_type deque_allocator;
        size_type _buffer_size;

        typename allocator_type::template rebind<pointer>::other map_allocator;

    public:
        deque(const allocator_type &alloc = allocator_type())
            : map(0), map_size(0), deque_allocator(alloc), _buffer_size(4096)
        {
            create_map_and_nodes(0);
        }

        explicit deque(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
            : map(0), map_size(0), deque_allocator(alloc), _buffer_size(4096)
        {
            fill_initialize(n, val);
        }

        template <class InputIterator>
        deque(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type())
            : map(0), map_size(0), deque_allocator(alloc), _buffer_size(4096)
        {
            create_map_and_nodes(0);
            insert(begin(), first, last);
        }

        deque(const deque &x) : map(0), map_size(0), deque_allocator(x.deque_allocator), _buffer_size(4096) // deque(x.begin(), x.end(), x.deque_allocator)
        {
            map_allocator = x.map_allocator;
            create_map_and_nodes(0);
            insert(begin(), x.begin(), x.end());
        }

        ~deque()
        {
            clear();
            deallocate_node(*(start.node)); //39t bik
            map_allocator.deallocate(map, map_size);
        }

        void swap(deque &x)
        {
            ft::swap(x.start, start);
            ft::swap(x.finish, finish);
            ft::swap(x.deque_allocator, deque_allocator);
            ft::swap(x.map_allocator, map_allocator);
            ft::swap(x.map, map);
            ft::swap(x.map_size, map_size);
            ft::swap(x._buffer_size, _buffer_size);
        }

        deque &operator=(const deque &x)
        {
            if (&x == this)
                return *this;
            deque d(x);
            this->swap(d);

            return *this;
        }


        void fill_initialize(size_t n, const value_type &value)
        {
            create_map_and_nodes(n);

            for (map_pointer cur = start.node; cur < finish.node; ++cur)
                initialized_fill_node(*cur, *cur + buffer_size(), value);

            initialized_fill_node(finish.first, finish.cur, value);
        }

        void initialized_fill_node(pointer first, pointer end, const value_type &value)
        {
            while (first != end)
            {
                deque_allocator.construct(first, value);
                ++first;
            }
        }

        iterator begin() { return start; }
        iterator end() { return finish; }
        const_iterator begin() const { return start; }
        const_iterator end() const { return finish; }
        reverse_iterator rbegin() { return reverse_iterator(end()); }
        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
        const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
        size_t deque_buf_size(size_t sz)
        {
            // i return how many elements can be stored
            return sz < _buffer_size ? size_t(_buffer_size / sz) : size_t(1);
        }
        size_t buffer_size()
        {
            return deque_buf_size(sizeof(T));
        }

        reference front()
        {
            return *start;
        }
        const_reference front() const
        {
            return *start;
        }
        reference back()
        {
            iterator answer = finish;
            answer--;
            return *answer;
        }
        const_reference back() const
        {
            iterator answer = finish;
            answer--;
            return *answer;
        }

        pointer allocate_node()
        {
            return deque_allocator.allocate(buffer_size());
        }

        void deallocate_node(pointer node)
        {
            deque_allocator.deallocate(node, buffer_size());
        }

        size_type size() const
        {
            return finish - start;
        }

        void create_map_and_nodes(size_type num_elements)
        {
            size_type num_of_nodes = num_elements / buffer_size() + 1;

            map_size = num_of_nodes + 2;

            map = map_allocator.allocate(map_size); //

            map_pointer new_start = map + (map_size - num_of_nodes) / 2;
            map_pointer new_finish = new_start + num_of_nodes - 1;

            map_pointer cur = new_start;
            while (cur <= new_finish)
            {
                *cur = allocate_node();
                cur++;
            }

            start.set_node(new_start);
            finish.set_node(new_finish);

            start.cur = start.first;
            finish.cur = finish.first + num_elements % buffer_size();

        }

        void copy(map_pointer s, map_pointer e, map_pointer ns)
        {
            while (s != e)
            {
                *ns = *s;
                ns++;
                s++;
            }
        }

        void copy_backward(map_pointer s, map_pointer e, map_pointer ns)
        {
            while (s != e)
            {
                e--;
                ns--;
                *ns = *e;
            }
        }

        void reallocate_map(size_type nodes_to_add, bool in_front = 0)
        {
            size_type num_old_nodes = finish.node - start.node + 1;
            size_type num_new_nodes = num_old_nodes + nodes_to_add;

            map_pointer new_nstart;
            if (map_size > 2 * num_new_nodes)
            {
                new_nstart = map + (map_size - num_new_nodes) / 2 + (in_front ? nodes_to_add : 0);
                if (new_nstart < start.node)
                    copy(start.node, finish.node + 1, new_nstart);
                else
                    copy_backward(start.node, finish.node + 1, new_nstart + num_old_nodes);
            }
            else
            {
                size_type new_map_size = map_size + (map_size > nodes_to_add ? map_size : nodes_to_add) + 2;
                map_pointer new_map = map_allocator.allocate(new_map_size);
                new_nstart = new_map + (new_map_size - num_new_nodes) / 2 + (in_front ? nodes_to_add : 0);
                copy(start.node, finish.node + 1, new_nstart);
                map_allocator.deallocate(map, map_size);
                map = new_map;
                // std::cout << new_map_size << ":;;;;;;;;;;;;;;;;;;\n";
                map_size = new_map_size;
            }
            start.set_node(new_nstart);
            finish.set_node(new_nstart + num_old_nodes - 1);
        }
        private:
            template <class RandomAccessIterator>
            void iter_swap(RandomAccessIterator first, RandomAccessIterator last)
            {
                typename RandomAccessIterator::value_type tmp = *first;
                *first = *last;
                *last = tmp;
            }

            template <class RandomAccessIterator>
            void reverse(RandomAccessIterator first, RandomAccessIterator last)
            {
                while (first<last)
                {
                    iter_swap(first++, --last);
                }
            }
    public:
        void push_back(const value_type &t)
        {

            if (finish.cur != finish.last - 1)
            {
                deque_allocator.construct(finish.cur, t);
                ++finish.cur;
            }
            else
            {
                move_back(t);
            }
        }

    private:
        void move_back(const value_type &t)
        {
            value_type val = t;
            reserve_map_back();

            *(finish.node + 1) = allocate_node();
            deque_allocator.construct(finish.cur, val);

            finish.set_node(finish.node + 1);
            finish.cur = finish.first;
        }

    public:
        void push_front(const value_type &x)
        {
            value_type val = x;

            if (start.cur != start.first)
            {
                deque_allocator.construct(start.cur - 1, val);
                --start.cur;
            }
            else
            {

                move_front(val);
            }
        }

    private:
        void move_front(const value_type &val)
        {
            reserve_map_front();
            *(start.node - 1) = allocate_node();

            start.set_node(start.node - 1);
            start.cur = start.last - 1;
            deque_allocator.construct(start.cur, val);
        }

        void reserve_map_back(size_type nodes_to_add = 1)
        {
            if (nodes_to_add + 1 > map_size - (finish.node - map))
                reallocate_map(nodes_to_add);
        }

        void reserve_map_front(size_type nodes_to_add = 1)
        {
            size_type sz = start.node - map;
            if (nodes_to_add > sz)
                reallocate_map(nodes_to_add, true);
        }

    public:
        void pop_back()
        {
            if (finish.cur != finish.first)
            {
                --finish.cur;
                deque_allocator.destroy(finish.cur);
            }
            else
                pop_back_free();
        }

        void pop_back_free()
        {
            deallocate_node(finish.first);
            finish.set_node(finish.node - 1);
            finish.cur = finish.last - 1;
            deque_allocator.destroy(finish.cur);
        }
        void pop_front()
        {
            if (start.cur != start.last - 1)
            {
                deque_allocator.destroy(start.cur);
                ++start.cur;
            }
            else
                pop_front_free();
        }

        void pop_front_free()
        {
            deque_allocator.destroy(start.cur);
            deallocate_node(start.first);
            start.set_node(start.node + 1);
            start.cur = start.first;
        }

        void destroy_buffer(pointer s, pointer e)
        {
            while (s != e)
            {
                deque_allocator.destroy(s);
                s++;
            }
        }

        void destroy_buffer_iterator(iterator s, iterator e)
        {
            while (s != e)
            {
                iterator next = s + 1;
                deque_allocator.destroy(s.cur);
                s = next;
            }
        }

    public:
        template <class InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            clear();
            insert(begin(), first, last);
        }

        void assign(size_type n, const value_type &val)
        {
            clear();
            insert(begin(), n, val);
        }

        size_type max_size() const
        {
            return size_t(-1);
        }
        allocator_type get_allocator() const
        {
            return deque_allocator;
        }
        void clear()
        {

            for (map_pointer node = start.node + 1; node < finish.node; ++node)
            {

                destroy_buffer(*node, *node + buffer_size());
                deallocate_node(*node); //
            }
            if (start.node != finish.node)
            {

                destroy_buffer(start.cur, start.last);
                destroy_buffer(finish.first, finish.cur);

                deallocate_node(finish.first);
            }
            else
                destroy_buffer(start.cur, finish.cur);

            finish = start;
        }

        void copy_backward(iterator s, iterator e, iterator ns)
        {
            while (s != e)
            {
                e--;
                ns--;
                *ns = *e;
            }
        }

        void copy(iterator s, iterator e, iterator ns)
        {
            while (s != e)
            {
                *ns = *s;
                s++;
                ns++;
            }
        }

    public:
        reference at(size_type pos)
        {
            if (pos >= size())
                throw ft::out_of_range("ddas");
            return operator[](pos);
        }

        const_reference at(size_type pos) const
        {
            if (pos >= size())
                throw ft::out_of_range("ddas");
            return operator[](pos);
        }
        iterator erase(iterator pos)
        {
            iterator next = pos;
            ++next;
            difference_type i = pos - start;

            if (static_cast<unsigned long long>(i) < (size() >> 1))
            {
                // g(55);
                copy_backward(start, pos, next);
                pop_front();
            }
            else
            {
                copy(next, finish, pos);
                pop_back();
            }
            return start + i;
        }

        iterator erase(iterator first, iterator last)
        {
            if (first == start && last == finish)
            {
                clear();
                return finish;
            }
            else
            {
                difference_type n = last - first;
                difference_type elems_before = first - start;

                if (static_cast<unsigned long long>(elems_before) < (size() - n) / 2)
                {
                    copy_backward(start, first, last);
                    iterator new_start = start + n;
                    destroy_buffer_iterator(start, new_start);

                    for (map_pointer cur = start.node; cur < new_start.node; ++cur)
                        deallocate_node(*cur);
                    start = new_start;
                }
                else
                {
                    copy(last, finish, first);
                    iterator new_finish = finish - n;
                    destroy_buffer_iterator(new_finish, finish);

                    for (map_pointer cur = new_finish.node + 1; cur <= finish.node; ++cur)
                        deallocate_node(*cur);
                    finish = new_finish;
                }
                return start + elems_before;
            }
        }

    public:
        iterator insert(iterator position, const value_type &x)
        {
            if (position.cur == start.cur)
            {
                push_front(x);
                return start;
            }
            else if (position.cur == finish.cur)
            {
                push_back(x);
                iterator tmp = finish;
                --tmp;
                return tmp;
            }
            else
                return insert_expand(position, x);
        }

        iterator insert_expand(iterator pos, const value_type &x)
        {
            size_type index = pos - start;
            value_type x_copy = x;


            if (index < size() / 2)
            {
                value_type xx = front();
                push_front(xx);
                iterator front1 = start;
                ++front1;
                iterator front2 = front1;
                ++front2;
                pos = start + index;
                iterator pos1 = pos;
                ++pos1;
                // g(6);
                copy(front2, pos1, front1);
                // g(6);
            }
            else
            {
                push_back(back());
                iterator back1 = finish;
                --back1;
                iterator back2 = back1;
                --back2;
                pos = start + index;

                copy_backward(pos, back2, back1);
            }
            *pos = x_copy;

            return pos;
        }

        reference operator[](size_type n)
        {
            return start[n];
        }

        const_reference operator[]( size_type n ) const
        {
            return start[n];
        }

        void resize(size_type n, value_type val = value_type())
        {
            size_type sz = size();
            if (n > sz)
            {
                while (sz < n)
                {
                    push_back(val);
                    sz++;
                }
            }
            else if (n < sz)
                erase(start + n, finish);
        }

        bool empty() const
        {
            return !size();
        }


    private:
        // For input iterators (slower, must iterate to count)
        template <class InputIt>
        void insert_dispatch(iterator pos, InputIt first, InputIt last,
                             std::input_iterator_tag)
        {
            if (first == last)
                return;
            for (; first != last; ++first, ++pos)
                pos = insert(pos, *first);
            return;
        }

        template <class InputIt>
        void insert_(iterator pos, InputIt first, InputIt last,
                     typename ft::enable_if<!ft::is_integral<InputIt>::value>::type * = 0)
        {
            insert_dispatch(pos, first, last,
                            typename ft::iterator_traits<InputIt>::iterator_category());
        }

        template <class InputIt>
        void insert_dispatch(iterator pos, InputIt first, InputIt last, std::forward_iterator_tag)
        {
            if (first == last)
                return;
            difference_type n = ft::distance(first, last);

            difference_type offset = pos - start;

            // If inserting at the beginning
            if (pos.cur == start.cur)
            {

                for (InputIt it = first; it != last; ++it)
                    push_front(*it);

                iterator old_start = start + n;
                this->reverse(start, old_start);
                return;
            }

            else if (pos.cur == finish.cur)
            {
                for (InputIt it = first; it != last; ++it)
                    push_back(*it);
                return;
            }

            else
            {

                if (offset < (long)size() / 2)
                {

                    for (difference_type i = 0; i < n; ++i)
                        push_front(front());

                    pos = start + offset + n;
                    iterator old_start = start + n;
                    iterator mid = old_start + offset;

                    copy(old_start, mid, start);
                    InputIt it = first;
                    for (iterator insert_pos = start + offset; insert_pos != pos && it != last; ++insert_pos, ++it)
                        *insert_pos = *it;
                }
                else
                {

                    for (difference_type i = 0; i < n; ++i)
                        push_back(back());

                    iterator old_finish = finish - n;
                    pos = start + offset;
                    iterator mid = pos;

                    copy_backward(mid, old_finish, finish);
                    InputIt it = first;
                    for (iterator insert_pos = pos; it != last; ++insert_pos, ++it)
                        *insert_pos = *it;
                }

                return;
            }
        }

        void insert_(iterator position, size_type n, const value_type &val)
        {
            difference_type offset = position - start;

            if (n == 0)
                return;

            // If inserting at the beginning
            if (position.cur == start.cur)
            {

                for (size_t it = 0; it < n; ++it)
                    push_front(val);

                iterator old_start = start + n;
                this->reverse(start, old_start);
                return;
            }

            else if (position.cur == finish.cur)
            {

                for (size_t it = 0; it < n; ++it)
                    push_back(val);

                return;
            }

            else
            {

                if (static_cast<unsigned long long>(offset) < size() / 2)
                {

                    for (size_type i = 0; i < n; ++i)
                        push_front(front());

                    position = start + offset + n;
                    iterator old_start = start + n;
                    iterator mid = old_start + offset;

                    copy(old_start, mid, start);

                    size_t it = 0;
                    for (iterator insert_pos = start + offset; insert_pos != position && it < n; ++insert_pos, ++it)
                    {
                        *insert_pos = val;
                    }
                }
                else
                {

                    for (size_type i = 0; i < n; ++i)
                        push_back(back());

                    iterator old_finish = finish - n;
                    position = start + offset;
                    iterator mid = position;

                    copy_backward(mid, old_finish, finish);
                    // InputIt it = first;
                    size_t it = 0;

                    for (iterator insert_pos = position; it < n; ++insert_pos, ++it)
                    {
                        *insert_pos = val;
                    }
                }
            }
        }

    public:
        template <class InputIt>
        void insert(iterator pos, InputIt first, InputIt last)
        {
            insert_(pos, first, last);
        }

        void insert(iterator position, size_type n, const value_type &val)
        {
            insert_(position, n, val);
        }
    };

    template <class T, class Alloc>
    bool operator==(const deque<T, Alloc> &lhs, const deque<T, Alloc> &rhs)
    {
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());

    }

    template <class T, class Alloc>
    void swap(deque<T, Alloc> &lhs, deque<T, Alloc> &rhs)
    {
        return lhs.swap(rhs);
    }

    template <class T, class Alloc>
    bool operator!=(const deque<T, Alloc> &lhs, const deque<T, Alloc> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Alloc>
    bool operator<(const deque<T, Alloc> &lhs, const deque<T, Alloc> &rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Alloc>
    bool operator<=(const deque<T, Alloc> &lhs, const deque<T, Alloc> &rhs)
    {
        return !(rhs < lhs);
    }

    template <class T, class Alloc>
    bool operator>(const deque<T, Alloc> &lhs, const deque<T, Alloc> &rhs)
    {
        return rhs < lhs;
    }

    template <class T, class Alloc>
    bool operator>=(const deque<T, Alloc> &lhs, const deque<T, Alloc> &rhs)
    {
        return !(lhs < rhs);
    }

}
