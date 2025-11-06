#include <cstddef>
#ifndef FT_ALGORITHM_HPP__

#define FT_ALGORITHM_HPP__

// i suppose i get a random_access_iterator_tag
#include "iterator_traits.hpp"
#include "functional.hpp"
#include <iostream>
namespace ft
{

    template <class RandomAccessIterator>
    void make_heap(RandomAccessIterator first, RandomAccessIterator last)
    {
        (void)last;
        (void)first;
    }

    template <class RandomAccessIterator, class Compare>
    void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
    {
        if (first == last)
            return;
        typename ft::iterator_traits<RandomAccessIterator>::difference_type pos = ft::distance(first, last);
        // silonze_t pos = last - first - 1;
        while (pos >= 0)
        {
            heapify_down(first, last, comp, pos);
            pos -= 1;
        }
    }

    template <class RandomAccessIterator>
    void push_heap(RandomAccessIterator first, RandomAccessIterator last)
    {
        pop_heap(first, last, ft::less<typename RandomAccessIterator::value_type>());
    }

    template <class T>
    void swap(T &a, T &b)
    {
        T tmp = a;
        a = b;
        b = tmp;
    }

    template <class RandomAccessIterator, class Compare>
    void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
    {

        if (first == last)
            return;

        size_t pos = last - first - 1;
        while (pos)
        {
            size_t parent = (pos - 1) / 2;
            if (comp(first[pos], first[parent]))
                return;
            ft::swap(first[parent], first[pos]);
            pos = parent;
        }
    }

    template <class RandomAccessIterator>
    void pop_heap(RandomAccessIterator first, RandomAccessIterator last)
    {
        pop_heap(first, last, ft::less<typename RandomAccessIterator::value_type>());
    }

    template <class RandomAccessIterator, class Compare>
    void heapify_down(RandomAccessIterator first, RandomAccessIterator last, Compare comp, size_t pos)
    { // 0 1 2 3 4
        size_t sz = last - first;
        size_t child_pos = 0;
        RandomAccessIterator c = first;
        while (pos < sz)
        {
            size_t left_child = pos * 2 + 1;
            size_t right_child = pos * 2 + 2;

            if (left_child >= sz)
                return;

            child_pos = left_child;
            if (right_child < sz) // if right exists i choose the bigger one;
                child_pos = comp(c[left_child], c[right_child]) ? right_child : left_child;

            if (comp(c[child_pos], c[pos])) // default it means if child is less than me : so i return
                return;

            ft::swap(first[child_pos], first[pos]);
            pos = child_pos;
        }
    }

    template <class RandomAccessIterator, class Compare>
    void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
    {
        if (first == last)
            return;

        ft::swap(*first, *(last - 1));
        heapify_down(first, last - 1, comp, 0);
    }

    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare(
        InputIterator1 first1, InputIterator1 last1,
        InputIterator2 first2, InputIterator2 last2,
        typename ft::enable_if<!ft::is_integral<InputIterator1>::value>::type * = 0,
        typename ft::enable_if<!ft::is_integral<InputIterator2>::value>::type * = 0)
    {
        while (first1 != last1)
        {
            if (first2 == last2)
                return false;

            if (*first1 < *first2)
                return true;

            if (*first2 < *first1)
                return false;

            ++first1;
            ++first2;
        }
        return first2 != last2;
    }


    template <class InputIterator1, class InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1, 
            InputIterator2 first2, InputIterator2 last2)
    {

        typename ft::iterator_traits<InputIterator1>::difference_type dist1 = ft::distance(first1, last1);
        typename ft::iterator_traits<InputIterator2>::difference_type dist2 = ft::distance(first2, last2);
        
        if (dist1 != dist2)
            return false;
        

        while (first1 != last1)
        {
            if (*first1 != *first2)
                return false;
            ++first1;
            ++first2;
        }
        return true;
    }


}

#endif