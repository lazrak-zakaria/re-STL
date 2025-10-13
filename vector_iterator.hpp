

namespace ft
{
    template <class T>
    class vector_iterator
    {

    public:
        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef long long difference_type;
        typedef T *pointer;
        typedef T &reference;

    private:
        pointer _ptr;

    public:
        vector_iterator() : _ptr(NULL)
        {
        }
        vector_iterator(pointer _ptr) : _ptr(_ptr)
        {
        }
        ~vector_iterator()
        {
        }
        template<class U>
        vector_iterator(const vector_iterator<U>& other)
                    // typename std::enable_if<std::is_convertible<U*, T*>::value>::type* = 0)
            : _ptr(other.base())
        {
        }

        pointer base() const
        {
            return _ptr;
        }
        reference operator*()
        {
            return *_ptr;
        }

        pointer operator->()
        {
            return _ptr;
        }

        vector_iterator &operator++()
        {
            ++_ptr;
            return *this;
        }

        vector_iterator operator++(int)
        {
            vector_iterator ans = *this;
            ++_ptr;
            return ans;
        }

        vector_iterator &operator--()
        {
            --_ptr;
            return *this;
        }

        vector_iterator operator--(int)
        {
            vector_iterator ans = *this;
            --_ptr;
            return ans;
        }

        vector_iterator &operator+=(difference_type n)
        {
            _ptr += n;
            return *this;
        }

        vector_iterator &operator-=(difference_type n)
        {
            _ptr -= n;
            return *this;
        }

        vector_iterator operator+(difference_type n) const
        {
            return vector_iterator(_ptr + n);
        }

        vector_iterator operator-(difference_type n) const
        {
            return vector_iterator(_ptr - n);
        }





        bool operator==( const vector_iterator &other) const
        {
            return _ptr == other._ptr;
        }

        bool operator!=( const vector_iterator &other) const
        {
            return _ptr != other._ptr;
        }

        reference operator[](difference_type n) const { return *(_ptr + n); }
        difference_type operator-(const vector_iterator &other) const { return _ptr - other._ptr; }
    };

};