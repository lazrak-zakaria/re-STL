

#ifndef FT_QUEUE__HPP_
#define FT_QUEUE__HPP_

/*

how to represent tree as an array
formula   2*i+1
          2*i+2

its parent =floor ((i-1/2))

*/
#include "algorithm.hpp"
#include "vector.hpp"
#include "deque.hpp"
#include "functional.hpp"
namespace ft
{

    template <class T, class Container = ft::vector<T>, class Compare = ft::less<typename Container::value_type> >
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
        container_type C;
        value_compare comp;

    private:
    public:
        explicit priority_queue(const Compare &comp = Compare(), const Container &ctnr = Container())
            : C(ctnr), comp(comp)
        {
            ft::make_heap(C.begin(), C.end(), comp);
        }

        template <class InputIterator>
        priority_queue(InputIterator first, InputIterator last, const Compare &comp = Compare(),
                       const Container &ctnr = Container()) : comp(comp), C(ctnr)
        {
            while (first != last)
            {
                C.push_back(*first);
                first++;
            }
            ft::make_heap(C.begin(), C.end(), comp);
        }

        ~priority_queue()
        {
        }

        void push(const value_type &val)
        {
            C.push_back(val);
            ft::push_heap(C.begin(), C.end(), comp);
        }

        void pop()
        {
            ft::pop_heap(C.begin(), C.end(), comp);
            C.pop_back();
        }
        bool empty() const
        {
            return !C.size();
        }

        const value_type &top() const
        {
            return C.front();
        }

        size_type size() const
        {
            return C.size();
        }

    };

    template <
        class T,
        class Container = ft::deque<T> >
    class queue
    {

    public:
        typedef Container container_type;

        typedef typename Container::value_type value_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::reference reference;
        typedef typename Container::const_reference const_reference;

    protected:
        container_type C;

    public:
        explicit queue(const container_type &ctnr = container_type()) : C(ctnr)
        {
        }
        ~queue()
        {}
        reference front()
        {
            return C.front();
        }
        const_reference front() const
        {
            return C.front();
        }

        reference back()
        {
            return C.back();
        }

        const_reference back() const
        {
            return C.back();
        }

        void push(const value_type &value)
        {
            C.push_back(value);
        }
        bool empty() const
        {
            return !C.size();
        }

        size_type size() const
        {
            return C.size();
        }

        void pop()
        {
            C.pop_front();
        }

        friend bool operator==(const queue &lhs,
                               const queue &rhs)
        {
            return lhs.C == rhs.C;
        }

        friend bool operator!=(const queue &lhs,
                               const queue &rhs)
        {
            return lhs.C != rhs.C;
        }

        friend bool operator<(const queue &lhs,
                              const queue &rhs)
        {
            return lhs.C < rhs.C;
        }

        friend bool operator<=(const queue &lhs,
                               const queue &rhs)
        {
            return lhs.C <= rhs.C;
        }

        friend bool operator>(const queue &lhs,
                              const queue &rhs)
        {
            return lhs.C > rhs.C;
        }

        friend bool operator>=(const queue &lhs,
                               const queue &rhs)
        {
            return lhs.C >= rhs.C;
        }
    };


}

#endif