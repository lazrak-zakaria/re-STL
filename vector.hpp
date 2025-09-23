#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include "iterator.hpp"
#define __RATIO__FT__VECTOR__ 2
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

        typedef unsigned long long size_type;
        typedef std::ptrdiff_t difference_type;

    private:
        value_type *_ptr;
        size_type _size;
        size_type _capacity;
        allocator_type _allocator;

    public:
        T pub;

        explicit vector(const allocator_type &alloc = allocator_type()) : _ptr(NULL), _size(0), _capacity(0), _allocator(alloc)
        {
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
            _allocator.deallocate(temp_ptr, old_capacity);
        }


        void resize (size_type n, value_type val = value_type())
        {
            if (n < _size)
            {
                for (int i = n; i < _size; ++i)
                {
                    _allocator.destroy(_ptr + i);
                }
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
    };

}

#endif
