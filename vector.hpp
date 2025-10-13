#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <memory>
#include "vector_iterator.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"

#define __RATIO__FT__VECTOR__ 2
#define __MAX_SIZE_FT_VECTOR__ 1073741823

namespace ft
{

    template <typename T, class Alloc = std::allocator<T>>
    class vector
    {

    public:
        typedef T value_type;
        typedef Alloc allocator_type;

        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

        typedef vector_iterator<T> iterator;
        typedef vector_iterator<const T> const_iterator;
        typedef reverse_iterator_<iterator> reverse_iterator;
        typedef reverse_iterator_<const_iterator> const_reverse_iterator;

        typedef unsigned long long size_type;
        typedef std::ptrdiff_t difference_type;

    private:
        value_type *_ptr = NULL;
        size_type _size = 0;
        size_type _capacity = 0;
        allocator_type _allocator;

    public:
        explicit vector(const allocator_type &alloc = allocator_type())
            : _ptr(NULL), _size(0), _capacity(0), _allocator(alloc)
        {
        }

        explicit vector(size_type n, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type()) : _allocator(alloc)
        {
            resize(n, val);
        }

        template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
               typename ft::enable_if<has_iterator_category<InputIterator>::value>::type * = 0) : _allocator(alloc)
        {
            insert(end(), first, last);
        }

        vector (const vector& x)
        {
            *this = x;
        }


        size_type size() const
        {
            return _size;
        }

        size_type capacity() const
        {
            return _capacity;
        }

        reference at(size_type n)
        {
            if (n < 0 || n >= _size)
                throw std::out_of_range("pos is out of range");
            return *(_ptr + n);
        }

        const_reference at(size_type n) const
        {
            if (n < 0 || n >= _size)
                throw std::out_of_range("pos is out of range");
            return *(_ptr + n);
        }

        void push_back(const value_type &val)
        {
            if (_size == _capacity)
            {
                if (_size)
                    reserve(_capacity * __RATIO__FT__VECTOR__);
                else
                    _ptr = _allocator.allocate(++_capacity);
            }
            _allocator.construct(_ptr + _size, val);
            _size++;
        }

        void pop_back()
        {
            if (_size)
            {
                _size--;
                _allocator.destroy(_ptr + _size);
            }
        }

        void reserve(size_type n)
        {
            if (n <= _capacity)
                return;

            value_type *temp_ptr = _ptr;
            size_type old_capacity = _capacity;
            _capacity = n;
            _ptr = _allocator.allocate(_capacity);
            for (int i = 0; i < _size; ++i)
            {
                _allocator.construct(_ptr + i, *(temp_ptr + i));
                _allocator.destroy(temp_ptr + i);
            }
            
            if (old_capacity)
                _allocator.deallocate(temp_ptr, old_capacity);
        }

        void resize(size_type n, value_type val = value_type())
        {
            if (n < _size)
            {
                for (int i = n; i < _size; ++i)
                {
                    _allocator.destroy(_ptr + i);
                }
                _allocator.deallocate(_ptr, _size);
                _size = n;
            }
            else if (n > _size)
            {
                if (n > _capacity)
                    reserve(n);
                for (int i = _size; i < n; ++i)
                    push_back(val);
            }
        }

        void clear()
        {
            resize(0);
        }

        bool empty() const
        {
            return _size == 0;
        }

        iterator insert(iterator position, const value_type &val)
        {
            difference_type pos = position - begin();

            if (pos == _size)
                push_back(val);
            else
                insert(position, 1, val);
            return iterator(_ptr + pos);
        }

        void insert(iterator position, size_type n, const value_type &val)
        {
            size_type available = _capacity - _size;
            difference_type pos = position - begin();

            if (n > available)
            {
                 value_type *temp_ptr = _ptr;
                size_type old_capacity = _capacity;
                _ptr = _allocator.allocate(_capacity * __RATIO__FT__VECTOR__ + n);
                _capacity = _capacity * __RATIO__FT__VECTOR__ + n;

                size_type i = 0;
                for ( ; i < pos; ++i){
                    _allocator.construct(_ptr + i, *(temp_ptr + i));
                    _allocator.destroy(temp_ptr + i);
                }

                for (size_type j = 0 ; j < n; ++j )
                    _allocator.construct(_ptr + i + j, val);

                size_type offset = n;
                for (; i < _size; ++i)
                    _allocator.construct(_ptr + i + offset, *(temp_ptr + i));
                    _allocator.destroy(temp_ptr + i);

                if (temp_ptr)
                    _allocator.deallocate(temp_ptr, old_capacity);
                _size += n;
            }
            else
            {
                size_type ending_pos = _size + n - 1;
                while (ending_pos != pos + n - 1)
                {
                    _allocator.construct(_ptr + ending_pos, *(_ptr + (ending_pos - n)));
                    _allocator.destroy(_ptr + (ending_pos - n));
                    ending_pos--;
                }
                for (int i = 0; i < n; ++i)
                    _allocator.construct(_ptr + pos + i, val);
                _size += n;
            }
        }

        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<has_iterator_category<InputIterator>::value>::type * = 0)
        {
            // later i should i should implement func that gives the difference of two iters
            difference_type n = last - first;
            size_type available = _capacity - _size;
            difference_type pos = position - begin();

            if (n > available)
            {
                value_type *temp_ptr = _ptr;
                size_type old_capacity = _capacity;
                _ptr = _allocator.allocate(_capacity * __RATIO__FT__VECTOR__ + n);
                _capacity = _capacity * __RATIO__FT__VECTOR__ + n;

                difference_type i = 0;
                for ( ; i < pos; ++i){
                    _allocator.construct(_ptr + i, *(temp_ptr + i));
                    _allocator.destroy(temp_ptr + i);
                }

                for (difference_type j = 0 ; first != last; ++j, ++first )
                    _allocator.construct(_ptr + i + j, *first);

                difference_type offset = n;
                for (; i < _size; ++i)
                    _allocator.construct(_ptr + i + offset, *(temp_ptr + i));
                    _allocator.destroy(temp_ptr + i);

                if (temp_ptr)
                    _allocator.deallocate(temp_ptr, old_capacity);
                _size += n;
            }
            else
            {
                size_type ending_pos = _size + n - 1;
                while (ending_pos != pos + n - 1)
                {
                    _allocator.construct(_ptr + ending_pos, *(_ptr + (ending_pos - n)));
                    _allocator.destroy(_ptr + (ending_pos - n));
                    ending_pos--;
                }
                for (int i = 0; i < n && first != last; ++i, ++first)
                    _allocator.construct(_ptr + pos + i, *first);
                _size += n;
            }
        }


        iterator erase(iterator position)
        {
            return erase(position, position + 1);
        }

        iterator erase(iterator first, iterator last)
        {
            size_type pos = first - begin();
            size_type howmuch = last - first;

            for (int i = pos; i < pos + howmuch; ++i)
                _allocator.destroy(_ptr + i);

            iterator start = last;
            iterator finish = end();

            for (; start != finish; ++start, pos++)
            {
                _allocator.construct(_ptr + pos, *(_ptr + (start - begin())));
                _allocator.destroy(_ptr + (start - begin()));
            }
            _size -= howmuch;
            return first;
        }

        size_type max_size() const
        {
            return __MAX_SIZE_FT_VECTOR__;
        }

        // iterator
        iterator begin()
        {
            return iterator(_ptr);
        }

        const_iterator begin() const
        {
            return const_iterator(_ptr);
        }

        iterator end()
        {
            return iterator(_ptr + _size);
        }

        const_iterator end() const
        {
            return const_iterator(_ptr + _size);
        }

        reverse_iterator rbegin()
        {
            return (reverse_iterator(--end()));
        }
        const_reverse_iterator rbegin() const
        {
            return (const_reverse_iterator(--end()));
        }

        reverse_iterator rend()
        {
            return (reverse_iterator(--begin()));
        }

        const_reverse_iterator rend() const
        {
            return (const_reverse_iterator(--begin()));
        }

        reference operator[](size_type n)
        {
            return *(_ptr + n);
        }
        const_reference operator[](size_type n) const
        {
            return *(_ptr + n);
        }

        vector &operator=(const vector &x)
        {

            if (&x == this)
                return *this;
                clear();
            reserve(x.size());
            for (int i = 0; i < x.size(); i++)
                _allocator.construct(_ptr + i, *(x._ptr + i));
            _size = x.size();

            return *this;
        }
    };
}

#endif
