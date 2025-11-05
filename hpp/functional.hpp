

#ifndef FT_FUNCTIONAL_HPP
#define FT_FUNCTIONAL_HPP

namespace ft
{

    template <
        class Arg1,
        class Arg2,
        class Result>
    struct binary_function
    {
        public:
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
        typedef Result result_type;
    };

    template <typename T>
    struct less : ft::binary_function<T, T, bool>
    {
        bool operator()(const T& lhs, const T& rhs) const {
            return lhs < rhs;
        }
    };


    template <typename T>
    struct equal_to : ft::binary_function<T, T, bool>
    {
        bool operator()(const T& lhs, const T& rhs) const {
            return lhs == rhs;
        }
    };




}

#endif
