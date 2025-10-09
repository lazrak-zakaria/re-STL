#include <cstddef>
#ifndef FT_ALGORITHM_HPP__

#define FT_ALGORITHM_HPP__

// i suppose i get a random_access_iterator_tag

namespace ft
{

    template <class RandomAccessIterator>
    void make_heap(RandomAccessIterator first, RandomAccessIterator last)
    {
    }

    template <class RandomAccessIterator, class Compare>
    void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
    {
        if (first == last)
            return;
        size_t pos = last - first - 1;
        while (pos >= 0)
        {
            heapify_down(first, last, comp, pos)
                pos -= 1;
        }
    }

    template <class RandomAccessIterator>
    void push_heap(RandomAccessIterator first, RandomAccessIterator last)
    {
        pop_heap(first, second, std::less<typename RandomAccessIterator::value_type>);
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
        pop_heap(first, last, std::less<typename RandomAccessIterator::value_type>);
    }

    template <class RandomAccessIterator, class Compare>
    void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
    {
        if (first == last)
            return;

        ft::swap(*first, *(last - 1));
        heapify_down(first, last - 1, comp, 0);
    }

    template <class RandomAccessIterator, class Compare>
    void heapify_down(RandomAccessIterator first, RandomAccessIterator last, Compare comp, size_t pos)
    {
        size_t sz = last - first;
        size_t child_pos = 0;

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
        }
    }
}

#endif