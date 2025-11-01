

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
#include <deque>
#include "vector.hpp"
namespace ft
{
    template <class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type> >
    class priority_queue
    {
    private:
    public:
        typedef Container container_type;
        typedef Compare value_compare;
        typedef typename Container::value_type value_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::reference reference;
        typedef typename Container::const_reference const_reference;

    protected:
        container_type c;
        value_compare comp;

    private:
    public:
        explicit priority_queue(const Compare &comp = Compare(), const Container &ctnr = Container()) : comp(comp), c(ctnr)
        {

            ft::make_heap(c.begin(), c.end());
        }

        template <class InputIterator>
        priority_queue(InputIterator first, InputIterator last, const Compare &comp = Compare(),
                       const Container &ctnr = Container()) : comp(comp), c(ctnr)
        {
            while (first != last)
            {
                c.push_back(*first);
                first++;
            }
            ft::make_heap(c.begin(), c.end());
        }

        ~priority_queue()
        {
        }

        void push(const value_type &val)
        {
            c.push_back(val);
            ft::push_heap(c.begin(), c.end(), comp);
        }

        void pop()
        {
            ft::pop_heap(c.begin(), c.end(), comp);
            c.pop_back();
        }
        bool empty() const
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

        // priority_queue &operator=(const priority_queue &other);
        // (1)(implicitly declared)
    };

    template <
        class T,
        class Container = std::deque<T> >
    class queue
    {

    public:
        typedef Container container_type;

        typedef typename Container::value_type value_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::reference reference;
        typedef typename Container::const_reference const_reference;

    protected:
        container_type c;

    public:
        explicit queue(const container_type &ctnr = container_type()) : c(ctnr)
        {
        }

        reference front()
        {
            return c.front();
        }
        const_reference front() const
        {
            return c.front();
        }

        reference back()
        {
            return c.back();
        }

        const_reference back() const
        {
            return c.back();
        }

        void push(const value_type &value)
        {
            c.push_back(value);
        }
        bool empty() const
        {
            return !c.size();
        }

        size_type size() const
        {
            return c.size();
        }

        void pop()
        {
            c.pop_front();
        }

        friend bool operator==(const queue &lhs,
                               const queue &rhs)
        {
            return lhs.c == rhs.c;
        }

        friend bool operator!=(const queue &lhs,
                               const queue &rhs)
        {
            return lhs.c != rhs.c;
        }

        friend bool operator<(const queue &lhs,
                              const queue &rhs)
        {
            return lhs.c < rhs.c;
        }

        friend bool operator<=(const queue &lhs,
                               const queue &rhs)
        {
            return lhs.c <= rhs.c;
        }

        friend bool operator>(const queue &lhs,
                              const queue &rhs)
        {
            return lhs.c > rhs.c;
        }

        friend bool operator>=(const queue &lhs,
                               const queue &rhs)
        {
            return lhs.c >= rhs.c;
        }
    };

}

#endif