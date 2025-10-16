

#include <memory>
#include "deque_iterator.hpp"

#define h std::cout << "here\n"
#define g(x) std::cout << "here: " << x << "\n"

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
        typedef typename std::allocator_traits<Allocator>::pointer pointer;
        typedef typename std::allocator_traits<Allocator>::const_pointer const_pointer;
        typedef value_type &reference;
        typedef const value_type &const_reference;

        typedef unsigned long size_type;
        typedef long difference_type;
        typedef deque_iterator<T, T &, T *> iterator;

    protected:
        typedef pointer *map_pointer;

    protected:
        iterator start;
        iterator finish;

        map_pointer map;
        size_type map_size;
        size_type _buffer_size = 4096;

        allocator_type deque_allocator;
        // std::allocator<value_type *> map_allocator ;
        typename allocator_type::template rebind<pointer>::other map_allocator;

    public:
        deque() : start(), finish(), map(0), map_size(0) { create_map_and_nodes(0); }
        iterator begin() { return start; }
        iterator end() { return finish; }

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

        reference back()
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

            map_size = std::max(map_size, num_of_nodes + 2);
            h;
            std::cout << map_size << "\n";
            map = map_allocator.allocate(map_size); //
            // i want my starting point to be in the middle
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
            // finish.cur = new int(3);
            // std::cout << * finish.cur << "--\n";
            h;
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
                size_type new_map_size = map_size + max(map_size, nodes_to_add) + 2;
                map_pointer new_map = map_allocator.allocate(new_map_size);
                new_nstart = new_map + (new_map_size - num_new_nodes) / 2 + (in_front ? nodes_to_add : 0);
                copy(start.node, finish.node + 1, new_nstart);
                map_allocator.deallocate(map, map_size);
                map = new_map;
                map_size = new_map_size;
            }
            start.set_node(new_nstart);
            finish.set_node(new_nstart + num_old_nodes - 1);
        }

    public: // push_* and pop_*
        void push_back(const value_type &t)
        {

            if (finish.cur != finish.last - 1)
            {
                deque_allocator.construct(finish.cur, t);
                h;
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
            if (!size())
            {
                push_back(val);
                return;
            }
            if (start.cur != start.first)
            {
                deque_allocator.construct(start.cur - 1, val);
                --start.cur;
            }
            else
                move_front(val);
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
            if (nodes_to_add > start.node - map)
                reallocate_map(nodes_to_add, true);
        }

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

        void clear()
        {

            for (map_pointer node = start.node + 1; node < finish.node; ++node)
            {

                destroy_buffer(*node, *node + buffer_size());

                deallocate_node(*node);
            }

            if (start.node != finish.node)
            {
                destroy_buffer(start.cur, start.last);
                destroy_buffer(finish.first, finish.cur);

                deque_allocator.deallocate(finish.first, buffer_size());
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
                // *ns.cur = *s.cur;
                *ns = *s;
                s++;
                ns++;
            }
        }

    public:
        iterator erase(iterator pos)
        {
            iterator next = pos;
            ++next;
            difference_type i = pos - start;

            if (i < (size() >> 1))
            {
                g(55);
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

                if (elems_before < (size() - n) / 2)
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
            difference_type index = pos - start;
            value_type x_copy = x;
            std::cout<< *begin() << "++\n";

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
                g(6);
                copy(front2, pos1, front1);
                g(6);

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
            std::cout<< *begin() << "++\n";
            return pos;
        }

        reference operator[](size_type n)
        {
            return start[n];
        }
    };

}
