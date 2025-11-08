#ifndef FT_REVERSE_ITER
#define FT_REVERSE_ITER

#include <iterator>

namespace ft
{

    template <typename Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::iterator_category iterator_category;
    };

    template <typename T>
    struct iterator_traits<T *>
    {
        typedef long difference_type;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef std::random_access_iterator_tag iterator_category;
    };

    template <typename T>
    struct iterator_traits<const T *>
    {
        typedef long difference_type;
        typedef T value_type;
        typedef const T *pointer;
        typedef const T &reference;
        typedef std::random_access_iterator_tag iterator_category;
    };

    // https://jguegant.github.io/blogs/tech/sfinae-introduction.html
    template <typename T>
    struct has_iterator_category
    {
    private:
        typedef char yes[1];
        typedef char no[2];

        template <typename U>
        static yes &test(typename U::iterator_category *);

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

    template <typename InputIterator>
    typename iterator_traits<InputIterator>::difference_type
    iter_distance(InputIterator first, InputIterator last, std::input_iterator_tag)
    {
        typename iterator_traits<InputIterator>::difference_type n = 0;
        while (first != last)
        {
            ++first;
            ++n;
        }
        return n;
    }

    template <typename RandomAccessIterator>
    typename iterator_traits<RandomAccessIterator>::difference_type
    iter_distance(RandomAccessIterator first, RandomAccessIterator last,
                  std::random_access_iterator_tag)
    {
        return last - first;
    }

    template <typename Iterator>
    typename iterator_traits<Iterator>::difference_type
    distance(Iterator first, Iterator last)
    {
        return iter_distance(first, last, typename iterator_traits<Iterator>::iterator_category());
    }

    template <typename T>
    struct is_integral
    {
        static const bool value = false;
    };

    // Specialize for all integral types
    template <>
    struct is_integral<bool>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<char>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<signed char>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<unsigned char>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<wchar_t>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<short>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<unsigned short>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<int>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<unsigned int>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<long>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<unsigned long>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<long long>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<unsigned long long>
    {
        static const bool value = true;
    };

    template <class _iterator>
    class reverse_iterator_
    {
    private:
        _iterator iter;

    public:
        typedef _iterator iterator_type;
        typedef typename ft::iterator_traits<_iterator>::iterator_category iterator_category;
        typedef typename ft::iterator_traits<_iterator>::value_type value_type;
        typedef typename ft::iterator_traits<_iterator>::difference_type difference_type;
        typedef typename ft::iterator_traits<_iterator>::pointer pointer;
        typedef typename ft::iterator_traits<_iterator>::reference reference;

        reverse_iterator_() : iter() {}

        explicit reverse_iterator_(_iterator iter) : iter(iter) {}

        template <class U>
        reverse_iterator_(const reverse_iterator_<U> &other) : iter(other.base()) {}

        _iterator base() const
        {
            return iter;
        }

        reference operator*() const
        {
            _iterator tmp = iter;
            return *(--tmp);
        }

        pointer operator->() const
        {
            return &(operator*());
        }

        reverse_iterator_ &operator++()
        {
            --iter;
            return *this;
        }

        reverse_iterator_ operator++(int)
        {
            reverse_iterator_ ans = *this;
            --iter;
            return ans;
        }

        reverse_iterator_ &operator--()
        {
            ++iter;
            return *this;
        }

        reverse_iterator_ operator--(int)
        {
            reverse_iterator_ ans = *this;
            ++iter;
            return ans;
        }

        reverse_iterator_ &operator+=(difference_type n)
        {
            iter -= n;
            return *this;
        }

        reverse_iterator_ &operator-=(difference_type n)
        {
            iter += n;
            return *this;
        }

        reverse_iterator_ operator+(difference_type n) const
        {
            return reverse_iterator_(iter - n);
        }

        reverse_iterator_ operator-(difference_type n) const
        {
            return reverse_iterator_(iter + n);
        }

        difference_type operator-(const reverse_iterator_ &other) const
        {
            return other.base() - iter;
        }

        reference operator[](difference_type n) const
        {
            return *(*this + n);
        }
    };

    template <class T, class U>
    bool operator==(const reverse_iterator_<T> &lhs, const reverse_iterator_<U> &rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <class T, class U>
    bool operator!=(const reverse_iterator_<T> &lhs, const reverse_iterator_<U> &rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <class T, class U>
    bool operator<(const reverse_iterator_<T> &lhs, const reverse_iterator_<U> &rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <class T, class U>
    bool operator<=(const reverse_iterator_<T> &lhs, const reverse_iterator_<U> &rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <class T, class U>
    bool operator>(const reverse_iterator_<T> &lhs, const reverse_iterator_<U> &rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <class T, class U>
    bool operator>=(const reverse_iterator_<T> &lhs, const reverse_iterator_<U> &rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <class Iterator>
    reverse_iterator_<Iterator> operator+(
        typename reverse_iterator_<Iterator>::difference_type n,
        const reverse_iterator_<Iterator> &rev_it)
    {
        return rev_it + n;
    }

}
#endif