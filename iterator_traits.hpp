

#ifndef FT_ITERATOR_TRAITS_
#define FT_ITERATOR_TRAITS_



namespace ft
{
    // https://jguegant.github.io/blogs/tech/sfinae-introduction.html
    template <typename T>
    struct has_iterator_category
    {
    private:
        typedef char yes[1];
        typedef char no[2];
    
        template <typename U>
        static yes &test(typename std::iterator_traits<U>::iterator_category *); // later i should do my own iterator traits
    
        template <typename U>
        static no &test(...);
    
    public:
        static const bool value = sizeof(test<T>(0)) == sizeof(yes);
    };
    
    template <bool B, class T = void>
    struct enable_if
    {
    };
    
    template <class T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

}

#endif