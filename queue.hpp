

#ifndef FT_QUEUE__HPP_
#define FT_QUEUE__HPP_

/*

how to represent tree as an array
formula   2*i+1
          2*i+2

its parent =floor ((i-1/2))

*/

#include <vector>

namespace ft
{
    template <class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type>>
    class priority_queue
    {
    private:
    public:
        typedef Container container_type;
        typedef T value_type;
        typedef size_t size_type;
        typedef Compare value_compare;

    protected:
        container_type c;
        value_compare cmp;

    private:
        size_t parent(size_t i)
        {
            if (!i || i >= c.size())
                return -1;
            return (i - 1) / 2
        }
        size_t child_left(size_t i)
        {
            if (!i || i >= c.size())
                return -1;
            return 2 * i + 1;
        }
        size_t child_right(size_t i)
        {
            if (!i || i >= c.size())
                return -1;
            return 2 * i + 2;
        }

        void heapify_up(size_t node)
        {
            if (!node || node >= c.size())
                return;
            size_t parent_ = parent(node);
            if (parent_ < c.size() && cmp(c[node], c[parent_]))
                return;
            ////swap
            value_type t = c[parent_];
            c[parent_] = c[node];
            c[node] = t;

            heapify_up(parent_);
        }

        void heapify_down(size_t node)
        {
            if (node >= c.size())
                return;

            size_t left_child = child_left(node);
            size_t right_child = child_right(node);

            size_t child_pos = -1;
            // i need the min one

            if (left_child == child_pos) // no childs
                return;

            child_pos = right_child != child_pos && cmp(c[left_child], c[right_child]) ? right_child : left_child;

            if (cmp(c[child_pos], c[node]))
                return;

            ////swap
            value_type t = c[child_pos];
            c[child_pos] = c[node];
            c[node] = t;

            heapify_down(child_pos);
        }

        public:
            void  push (const value_type& val)
            {
                c.push_back(val);
                heapify_up(c.size()-1);
            }

            void pop ()
            {
                if (empty())
                    return ;

                c[0] = c[c.size()-1];

                c.pop_back();
                heapify_down(0);
            }
            bool empty()
            {
                return ! c.size();
            }

            const value_type& top() const
            {
                return c.front();
            }

            size_type size() const
            {
                return c.size();
            }
    };

}

#endif