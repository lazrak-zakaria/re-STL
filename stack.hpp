#ifndef FT_STACK__HPP_
#define FT_STACK__HPP_


#include "deque.hpp"

namespace ft
{

    template <
        class T,
        class Container = ft::deque<T> >
    class stack
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
        explicit stack(const container_type &ctnr = container_type()) : c(ctnr)
        {
        }

        reference top()
        {
            return c.back();
        }

        const_reference top() const
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
            c.pop_back();
        }

        friend bool operator==(const stack &lhs,
                               const stack &rhs)
        {
            return lhs.c == rhs.c;
        }

        friend bool operator!=(const stack &lhs,
                               const stack &rhs)
        {
            return lhs.c != rhs.c;
        }

        friend bool operator<(const stack &lhs,
                              const stack &rhs)
        {
            return lhs.c < rhs.c;
        }

        friend bool operator<=(const stack &lhs,
                               const stack &rhs)
        {
            return lhs.c <= rhs.c;
        }

        friend bool operator>(const stack &lhs,
                              const stack &rhs)
        {
            return lhs.c > rhs.c;
        }

        friend bool operator>=(const stack &lhs,
                               const stack &rhs)
        {
            return lhs.c >= rhs.c;
        }
    };

}

#endif