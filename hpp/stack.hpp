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
        container_type C;

    public:
        explicit stack(const container_type &ctnr = container_type()) : C(ctnr)
        {
        }

        ~stack()
        {
        }

        reference top()
        {
            return C.back();
        }

        const_reference top() const
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
            C.pop_back();
        }

        friend bool operator==(const stack &lhs,
                               const stack &rhs)
        {
            return lhs.C == rhs.C;
        }

        friend bool operator!=(const stack &lhs,
                               const stack &rhs)
        {
            return lhs.C != rhs.C;
        }

        friend bool operator<(const stack &lhs,
                              const stack &rhs)
        {
            return lhs.C < rhs.C;
        }

        friend bool operator<=(const stack &lhs,
                               const stack &rhs)
        {
            return lhs.C <= rhs.C;
        }

        friend bool operator>(const stack &lhs,
                              const stack &rhs)
        {
            return lhs.C > rhs.C;
        }

        friend bool operator>=(const stack &lhs,
                               const stack &rhs)
        {
            return lhs.C >= rhs.C;
        }
    };

}

#endif