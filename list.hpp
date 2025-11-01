#ifndef FT_LIST_HPP__
#define FT_LIST_HPP__

#include <memory>
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "algorithm.hpp"

namespace ft
{

    template <class K>
    class lst_node
    {
    public:
        K key;
        lst_node *prev;
        lst_node *next;

        lst_node(K key) : key(key), prev(NULL), next(NULL)
        {
        }
    };
}
#include "list_iterator.hpp"
namespace ft
{
    template <
        class T,
        class Allocator = std::allocator<T> >
    class list
    {

    private:
    public:
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
        typedef lst_iterator<T> iterator;
        typedef lst_iterator<const T> const_iterator;
        typedef ft::reverse_iterator_<iterator> reverse_iterator;
        typedef ft::reverse_iterator_<const_iterator> const_reverse_iterator;

    private:
        typedef lst_node<value_type> *lst_node_ptr;

        lst_node_ptr head;


        typename allocator_type::template rebind<lst_node<value_type> >::other alloc;

        lst_node_ptr create_lst_node(const value_type &val)
        {
            lst_node_ptr n = alloc.allocate(1);
            alloc.construct(n, val);

            return n;
        }

        void delete_lst_node(lst_node_ptr n)
        {
            alloc.destroy(n);
            alloc.deallocate(n, 1);

        }

        void initialize()
        {
            head = create_lst_node(value_type());

            head->next = head;
            head->prev = head;

        }

    public:
        explicit list(const allocator_type &a = allocator_type()) : alloc(a)
        {
            initialize();
        }
        explicit list(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
            : list(alloc)
        {
            insert(begin(), n, val);
        }
        template <class InputIterator>
        list(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) : list(alloc)
        {
            insert(begin(), first, last);
        }

        list(const list &x) : list(x.alloc)
        {
            insert(begin(), x.begin(), x.end());
        }

        ~list()
        {
            clear();
            delete_lst_node(head);
        }

        list &operator=(const list &x)
        {
            if (this == &x)
                return *this;
            clear();
            insert(begin(), x.begin(), x.end());
            return *this;
        }

        template <class InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            clear();
            insert(begin(), first, last);
        }

        void assign(size_type n, const value_type &val)
        {
            clear();
            insert(begin(), n, val);
        }

        iterator begin()
        {
            return iterator(head->next);
        }
        const_iterator begin() const
        {
            return iterator(head->next);
        }
        iterator end()
        {
            return iterator(head);
        }
        const_iterator end() const
        {
            return iterator(head);
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end());
        }
        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }
        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(begin());
        }

        bool empty() const
        {
            return head == head->next;
        }

        size_t size() const
        {
            return ft::distance(begin(), end());
        }

        reference front()
        {
            return *begin();
        }
        reference back()
        {
            return *(--end());
        }

        const_reference front() const
        {
            return *begin();
        }
        const_reference back() const
        {
            return *(--end());
        }

        void link(lst_node_ptr f, lst_node_ptr s)
        {
            if (f)
                f->next = s;
            if (s)
                s->prev = f;
        }

    public:
        iterator insert(iterator position, const value_type &val)
        {
            lst_node_ptr tmp = create_lst_node(val);
            lst_node_ptr prev = position.node->prev;
            link(prev, tmp);
            link(tmp, position.node);
            return iterator(tmp);
        }

        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last)
        {
            for (; first != last; ++first)
            insert(position, *first);
        }
        void insert(iterator position, size_type n, const value_type &val)
        {
            while (n--)
                insert(position, val);
        }

        void push_front(const value_type &val)
        {
            insert(begin(), val);
        }
        void push_back(const T &val)
        {
            insert(end(), val);
        }

        iterator erase(iterator position)
        {
            lst_node_ptr next = position.node->next;
            lst_node_ptr prev = position.node->prev;
            link(prev, next);
            delete_lst_node(position.node);
            return iterator(next);
        }
        iterator erase(iterator first, iterator last)
        {
            while (first != last)
                erase(first++);
            return last;
        }

        void pop_front()
        {
            erase(begin());
        }

        void pop_back()
        {
            iterator tmp = end();
            erase(--tmp);
        }

        void clear()
        {
            lst_node_ptr cur = head->next;
            while (cur != head)
            {
                lst_node_ptr tmp = cur->next;
                delete_lst_node(cur);
                cur = tmp;
            }

            head->next = head;
            head->prev = head;
        }

        void remove(const T &value)
        {
            iterator first = begin();
            iterator last = end();
            while (first != last)
            {
                iterator next = first;
                ++next;
                if (*first == value)
                    erase(first);
                first = next;
            }
        }

        template <class Predicate>
        void remove_if(Predicate pred)
        {
            iterator first = begin();
            iterator last = end();
            while (first != last)
            {
                iterator next = first;
                ++next;
                if (pred(*first))
                    erase(first);
                first = next;
            }
        }

        size_type max_size() const
        {
            return size_type(-1);
        }

        void unique()
        {
            unique(std::equal_to<value_type>());
        }
        template <class BinaryPredicate>
        void unique(BinaryPredicate binary_pred)
        {
            iterator first = begin();
            iterator last = end();
            if (first == last)
                return;
            iterator next = first;
            while (++next != last)
            {
                if (binary_pred(*first, *next))
                    erase(next);
                else
                    first = next;
                next = first;
            }
        }

    private:
        void transfer(iterator position, iterator first, iterator last)
        {
            if (position != last)
            {
                last.node->prev->next = position.node;
                first.node->prev->next = last.node;
                position.node->prev->next = first.node;
                lst_node_ptr tmp = position.node->prev;
                position.node->prev = last.node->prev;
                last.node->prev = first.node->prev;
                first.node->prev = tmp;
            }
        }

    public:
        void merge(list &x)
        {
            merge(x, std::less<value_type>());
        }

        template <class Compare>
        void merge(list &x, Compare comp)
        {
            iterator first1 = begin();
            iterator last1 = end();
            iterator first2 = x.begin();
            iterator last2 = x.end();

            while (first1 != last1 && first2 != last2)
            {
                if (comp(*first2, *first1))
                {
                    iterator next = first2;
                    transfer(first1, first2, ++next);
                    first2 = next;
                }
                else
                    ++first1;
            }
            if (first2 != last2)
                transfer(last1, first2, last2);
            // x.head->next = x.head;
            x.head->prev = x.head;
        }

        void swap(list &x)
        {
            ft::swap(x.head, head);
        }

        void splice(iterator position, list &x)
        {
            if (!x.empty())
                transfer(position, x.begin(), x.end());
        }
        void splice(iterator position, list &, iterator i)
        {
            iterator j = i;
            ++j;
            if (position == i || position == j)
                return;
            transfer(position, i, j);
        }
        void splice(iterator position, list &x, iterator first, iterator last)
        {
            if (first != last)
                transfer(position, first, last);
        }

        void sort()
        {
            sort(std::less<value_type>());
        }
        template <class Compare>
        void sort(Compare comp)
        {
            if (size() < 2)
                return;
            list<T, Allocator> carry;
            list<T, Allocator> counter[64];
            int fill = 0;

            while (!empty())
            {
                carry.splice(carry.begin(), *this, begin());
                int i = 0;
                while (i < fill && !counter[i].empty())
                {
                    counter[i].merge(carry, comp);
                    carry.swap(counter[i++]);
                }
                carry.swap(counter[i]);
                if (i == fill)
                    ++fill;
            }
            for (int i = 1; i < fill; ++i)
                counter[i].merge(counter[i - 1], comp);
            swap(counter[fill - 1]);
        }

        void reverse()
        {
            if (size() < 2)
                return;
            iterator first = begin();
            ++first;
            while (first != end())
            {
                iterator old = first;
                ++first;
                transfer(begin(), old, first);
            }
        }

        void resize(size_type n, value_type val = value_type())
        {
            size_type sz = size();

            if (n < sz)
            {
                size_type to_delete = sz - n;
                while (to_delete--)
                    pop_back();
            }
            else if (n > sz)
            {
                size_type to_add = n - sz;
                while (to_add--)
                    push_back(val);
            }
        }
    };








    template <class T, class Allocator>
    bool operator==(const list<T,  Allocator> &lhs, const list<T,  Allocator> &rhs)
    {
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Allocator>
    bool operator!=(const list<T,  Allocator> &lhs, const list<T,  Allocator> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Allocator>
    bool operator<(const list<T,  Allocator> &lhs, const list<T,  Allocator> &rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Allocator>
    bool operator>(const list<T,  Allocator> &lhs, const list<T,  Allocator> &rhs)
    {
        return (rhs < lhs);
    }

    template <class T, class Allocator>
    bool operator<=(const list<T,  Allocator> &lhs, const list<T,  Allocator> &rhs)
    {
        return !(lhs > rhs);
    }

    template <class T, class Allocator>
    bool operator>=(const list<T,  Allocator> &lhs, const list<T,  Allocator> &rhs)
    {
        return !(lhs < rhs);
    }








}
#endif