

#ifndef FT_QUEUE__HPP_
#define FT_QUEUE__HPP_

/*

how to represent tree as an array
formula   2*i+1
          2*i+2

its parent =floor ((i-1/2))

*/
#include "algorithm.hpp"
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
    public:
        explicit priority_queue(const Compare &comp = Compare(), const Container &ctnr = Container())::cmp(comp), c(cntr)
        {

            ft::make_heap(c.begin(), c.end());
        }

        template <class InputIterator>
        priority_queue(InputIterator first, InputIterator last, const Compare &comp = Compare(),
                       const Container &ctnr = Container()) : cmp(comp), c(cntr)
        {
            while (first != last)
            {
                c.push_back(*first);
                first++;
            }
            ft::make_heap(c.begin(), c.end());
        }

        void push(const value_type &val)
        {
            c.push_back(val);
            push_heap(c.begin(), c.end(), cmp);
        }

        void pop()
        {
            ft::pop_heap(c.begin(), c.end(), cmp);
            c.pop_back();
        }
        bool empty()
        {
            return !c.size();
        }

        const value_type &top() const
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