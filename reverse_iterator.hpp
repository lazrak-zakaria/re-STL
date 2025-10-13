#ifndef FT_REVERSE_ITER
#define FT_REVERSE_ITER

namespace ft
{

    template <class _iterator>
    class reverse_iterator_
    {
    private:
        _iterator iter;

    public:
        typedef typename _iterator::iterator_category iterator_category;
        typedef typename _iterator::value_type value_type;
        typedef typename _iterator::difference_type difference_type;
        typedef typename _iterator::pointer pointer;
        typedef typename _iterator::reference reference;

        reverse_iterator_(_iterator iter) : iter(iter)
        {
        }

        template <class U>
        reverse_iterator_(const reverse_iterator_<U> &other) : iter(other.base())
        {
        }

        // Add base() method to access the underlying iterator
        _iterator base() const
        {
            return iter;
        }

        reference operator*()
        {
            return *iter;
        }

        pointer operator->()
        {
            return iter;
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

        bool operator==(const reverse_iterator_ &other) const
        {
            return iter == other;
        }

        bool operator!=(const reverse_iterator_ &other) const
        {
            return iter != other;
        }

        reference operator[](difference_type n) const
        {
            return iter[-n];
        }
    };

}

#endif
