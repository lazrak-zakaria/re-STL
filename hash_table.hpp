#ifndef FT_HASH_TABLE_HPP
#define FT_HASH_TABLE_HPP

#include <memory>
#include <vector>
#include <utility>
#include "utility.hpp"
#include "iterator_traits.hpp"

namespace ft
{

    template <class K>
    struct hash_node
    {
        hash_node(const K &k)
            : key(k), next(0)
        {
        }

        K key;
        hash_node<K> *next;
    };

    template <class Key,
              class Hash = std::hash<Key>,
              class Pred = std::equal_to<Key>,
              class Alloc = std::allocator<Key>,
              bool Unique = true>
    class hash_table
    {
    private:
        typedef hash_node<Key> *hash_node_ptr;
        typedef hash_table<Key, Hash, Pred, Alloc> hash_table_self;
        typedef hash_table_self *hash_table_ptr;

    private:
        template <class T>
        class _iterator
        {
            hash_table_ptr ht;
            hash_node_ptr node;

        public:
            typedef std::forward_iterator_tag iterator_category;
            typedef T value_type;
            typedef long long difference_type;
            typedef T *pointer;
            typedef T &reference;

            _iterator(hash_node_ptr node, hash_table_ptr ht) : ht(ht), node(node)
            {
            }

            reference operator*() const
            {
                return node->key;
            }

            pointer operator->() const
            {
                return &node->key;
            }

            _iterator<T> &operator++()
            {
                if (node->next)
                    node = node->next;
                else
                {

                    size_t hsh = hasher()(node->key) % ht->table.size(); // curently i suppose the node->key is just one elmnt not a pair later add keyoftype
                    hsh++;
                    while (hsh < ht->table.size())
                    {
                        if (ht->table[hsh])
                            break;
                        hsh++;
                    }
                    if (hsh == ht->table.size())
                        node = nullptr;
                    else
                        node = ht->table[hsh];
                }
                return *this;
            }

            _iterator<T> operator++(int)
            {
                _iterator<T> ans = *this;
                ++(*this);
                return ans;
            }
            bool operator==(const _iterator<T> &oth) const
            {
                return this->ht == oth.ht && this->node == oth.node;
            }
        };

    public:
        typedef Key key_type;
        typedef Key value_type;
        typedef size_t size_type;
        typedef long difference_type;
        typedef Hash hasher;
        typedef Alloc allocator_type;
        typedef Pred key_equal;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef _iterator<Key> iterator;
        typedef _iterator<Key> const_iterator;

    public:
        std::vector<hash_node_ptr> table;
        size_t sz = 0;
        Pred cmp;
        float _max_load_factor = 1.0;

        size_t next_prime(size_t p)
        {
            static const int prime_sz = 28;
            static const unsigned long primes[] = {
                53, 97, 193, 389, 769,
                1543, 3079, 6151, 12289, 24593,
                49157, 98317, 196613, 393241, 786433,
                1572869, 3145739, 6291469, 12582917, 25165843,
                50331653, 100663319, 201326611, 402653189, 805306457,
                1610612741, 3221225473, 4294967291};
            for (int i = 0; i < prime_sz; ++i)
            {
                if (primes[i] > p)
                    return primes[i];
            }

            return primes[sz - 1];
        }

        void _copy(std::vector<hash_node_ptr> &from, std::vector<hash_node_ptr> &to)
        {
            for (size_t i = 0; i < table.size(); ++i)
            {
                hash_node_ptr cur = table[i];
                while (cur)
                {
                    table[i] = cur->next;
                    size_t hsh = hasher()(k) % n_table.size();
                    cur->next = n_table[hsh];
                    n_table[hsh] = cur;

                    cur = table[i];
                }
            }
        }

        ft::make_pair<iterator, bool> _insert(const key_type &k)
        {
            // if Unique and k exists return ;
            hash_node_ptr ptr = _find(k);
            if (Unique && ptr)
                return ft::make_pair(iterator(ptr, this), false);
            if (sz == table.size())
            {
                std::vector<hash_node_ptr> n_table(next_prime(table.size()));
                _copy(table, n_table);
                table.swap(n_table);
            }

            size_t hsh = hasher()(k) % table.size();
            hash_node_ptr node = new hash_node<Key>(k);
            node->next = table[hsh];
            table[hsh] = node;
            ++sz;

            return ft::make_pair(iterator(node, this), true);
        }

        hash_node_ptr _find(const key_type &k)
        {
            // cmp = Pred();

            if (table.empty())
                return nullptr;
            size_t hsh = hasher()(k) % table.size();

            hash_node_ptr ptr = table[hsh];

            while (ptr)
            {
                if (cmp(k, ptr->key))
                    break;
                ptr = ptr->next;
            }
            return ptr;
        }

        bool _erase(const key_type &k)
        {
            if (!_find(k))
                return false;

            size_t hsh = hasher()(k) % table.size();
            hash_node_ptr ptr = table[hsh];

            hash_node_ptr prev = nullptr;
            while (ptr)
            {
                if (*ptr == k)
                {
                    if (prev)
                        prev->next = ptr->next;
                    else
                        table[hsh] = ptr->next;
                    --sz;
                    break;
                }
                prev = ptr;
                ptr = ptr->next;
            }
            if (ptr)
                delete ptr;

            // should i check load_factor in erase ??
        }

        size_t bucket(const Key &key) const
        {
            return hasher()(key) % table.size();
        }

        size_t bucket_count() const
        {
            return table.size();
        }

    public:
        // Capacity
        bool empty() const noexcept
        {
            return !sz;
        }

        size_type size() const noexcept
        {
            return sz;
        }

        // Lookup
        size_type count(const Key &key) const
        {
            size_t ans = 0;
            if (empty())
                return ans;

            size_t hsh = hasher()(k) % table.size();
            hash_node_ptr ptr = table[hsh];
            while (ptr)
            {
                if (cmp(k, ptr->key))
                {
                    ans += 1;
                    if (Unique)
                        return ans;
                }
                ptr = ptr->next;
            }
            return ans;
        }

        iterator find(const Key &key)
        {
            hash_node_ptr ans = _find(key);
            return iterator(ans, this);
        }

        const_iterator find(key) const
        {
            hash_node_ptr ans = _find(key);
            return const_iterator(ans, this);
        }

    private:
        ft::pair<hash_node_ptr, hash_node_ptr>
        _equal_range(const Key &key)
        {
            hash_node_ptr start = find(key);

            if (!start)
                return ft::make_pair(start, start);

            if (Unique)
            {
                return ft::make_pair(start, start->next);
            }
            hash_node_ptr end = start;
            while (end && cmp(end->key, key))
                end = end->next;
            return ft::make_pair(start, end);
        }

    public:
        ft::pair<iterator, iterator>
        equal_range(const Key &key)
        {
            ft::pair<hash_node_ptr, hash_node_ptr> _ans = _equal_range(key);
            return ft::make_pair(iterator(_ans.first, this), iterator(_ans.second, this))
        }

        ft::pair<const_iterator, const_iterator>
        equal_range(const Key &key) const
        {
            ft::pair<hash_node_ptr, hash_node_ptr> _ans = _equal_range(key);
            return ft::make_pair(const_iterator(_ans.first, this), const_iterator(_ans.second, this))
        }

        // Hash policy

        float max_load_factor() const
        {
            return _max_load_factor;
        }
        void max_load_factor(float ml)
        {
            _max_load_factor = ml;
        }

        void rehash(size_type count)
        {
            size_t n = size() / max_load_factor();
            if (count >= n)
            {
                std::vector<hash_node_ptr> n_table(next_prime(count));
                _copy(table, n_table);
                table.swap(n_table);
            }
        }

        // void reserve()// calls ceil rehash;

        // modifiers

        std::pair<iterator, bool> insert(const value_type &value)
        {
            return _insert(value);
        }

        std::pair<iterator, bool> insert(value_type &&value)
        {
            return _insert(value);
        }

        iterator insert(const_iterator hint, const value_type &value)
        {
            return _insert(value).first;
        }

        iterator insert(const_iterator hint, value_type &&value)
        {
            return _insert(value).first;
        }

        template <class InputIt>
        void insert(InputIt first, InputIt last, typename ft::enable_if<has_iterator_category<InputIterator>::value>::type * = 0)
        {
            while (first != last)
            {
                _insert(*first);
                first++;
            }
        }



        iterator erase(const_iterator pos, const_iterator last)
        {

            size_t hsh = hasher()(pos.node->key) % table.size();

            hash_node_ptr ptr = table[hsh];

            hash_node_ptr prev = nullptr;
            while (ptr != last.node)
            {
                if (ptr == nullptr)
                {
                    prev = nullptr;
                    while (!table[hsh]) // default let it crash
                        hsh++;
                    ptr = table[hsh];
                    if (ptr == last.node)
                        return last;
                }

                if (prev)
                    prev->next = ptr->next;
                else
                    table[hsh] = ptr->next;
                --sz;

                prev = ptr;
                ptr = ptr->next;
            }
            if (ptr)
                delete ptr;
            return last;
        }

        iterator erase(iterator pos)
        {
           iterator _str = pos++;
            return erase(_str, pos);
        }

        iterator erase(const_iterator pos )
        {
            iterator _str = pos++;
            return erase(_str, pos);
        }

        size_type erase( const Key& key )
        {
            return _erase(key);
        }



    };

}

// bucket iterator later;
#endif