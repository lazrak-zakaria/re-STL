#ifndef FT_HASH_TABLE_HPP
#define FT_HASH_TABLE_HPP

#include <memory>
#include "vector.hpp"
#include <utility>
#include "utility.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"
#include "functional.hpp"



namespace ft
{

    template <class K>
    class HashFunc
    {
    public:
        size_t operator()(const K &key) const
        {
            return (size_t)key;
        }
    };

    template <>
    class HashFunc<std::string>
    {
    public:
        size_t operator()(const std::string &key) const
        {
            size_t val = 0;
            for (size_t i = 0; i < key.length(); ++i)
            {
                val *= 131;
                val += key[i];
            }

            return val;
        }
    };

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
              class Ky,
              class KeyType,
              class Hash = HashFunc<Ky>,
              class Pred = ft::equal_to<Key>,
              class Alloc = std::allocator<Key>,
              bool Unique = true>
    class hash_table
    {
    private:
        typedef hash_node<Key> *hash_node_ptr;
        typedef hash_table<Key, Ky, KeyType, Hash, Pred, Alloc> hash_table_self;
        typedef hash_table_self *hash_table_ptr;

        typedef KeyType key_of_type;

    private:
        template <class T>
        class _iterator
        {
            const hash_table *ht;
            hash_node_ptr node;

        public:
            friend class hash_table;

            typedef std::forward_iterator_tag iterator_category;
            typedef T value_type;
            typedef long long difference_type;
            typedef T *pointer;
            typedef const T &reference;

            _iterator(const hash_node_ptr &node, const hash_table *ht) : ht(ht), node(node)
            {
            }
            _iterator() : ht(NULL), node(NULL)
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

                    size_t hsh = ht->hash(key_of_type()(node->key)) % ht->table.size();
                    hsh++;
                    while (hsh < ht->table.size())
                    {
                        if (ht->table[hsh])
                            break;
                        hsh++;
                    }
                    if (hsh == ht->table.size())
                        node = NULL;
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
                return this->node == oth.node;
            }
            bool operator!=(const _iterator<T> &oth) const
            {
                return this->node != oth.node;
            }
        };

        template <class T>
        class _local_iterator
        {
            hash_node_ptr node;

        public:
            typedef std::forward_iterator_tag iterator_category;
            typedef T value_type;
            typedef long long difference_type;
            typedef T *pointer;
            typedef T &reference;

            _local_iterator(hash_node_ptr node) : node(node)
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
                node = node->next;
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
                return this->node == oth.node;
            }
        };

    public:
        typedef Ky key_type;
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
        typedef _local_iterator<Key> local_iterator;
        typedef _local_iterator<Key> const_local_iterator;

    private:
        ft::vector<hash_node_ptr> table;
        size_t sz;
        key_equal cmp;
        float _max_load_factor;
        hasher hash;
        typename allocator_type::template rebind<ft::hash_node<value_type> >::other alloc;

        allocator_type allocator;

        size_t next_prime(size_t p)
        {
            static const int prime_sz = 29;
            static const unsigned long primes[] = {
                53, 97, 193, 257, 389, 769,
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

        void _copy(ft::vector<hash_node_ptr> &from, ft::vector<hash_node_ptr> &to)
        {
            for (size_t i = 0; i < from.size(); ++i)
            {
                hash_node_ptr cur = from[i];
                while (cur)
                {
                    from[i] = cur->next;
                    size_t hsh = hash(key_of_type()(cur->key)) % to.size();
                    cur->next = to[hsh];
                    to[hsh] = cur;

                    cur = from[i];
                }
            }
        }

        ft::pair<iterator, bool> _insert(const value_type &k)
        {
            // if Unique and k exists return ;
            hash_node_ptr ptr = _find(key_of_type()(k));
            if (Unique && ptr)
                return ft::make_pair(iterator(ptr, this), false);

            size_t v = (sz + 1) / _max_load_factor;
            if (v > table.size())
                rehash(table.size());

            size_t hsh = hash((key_of_type()(k))) % table.size();
            hash_node_ptr node = create_node(k);
            node->next = table[hsh];
            table[hsh] = node;
            ++sz;

            return ft::make_pair(iterator(node, this), true);
        }

        hash_node_ptr _find(const Ky &k) const
        {
            if (table.empty())
                return NULL;
            size_t hsh = hash(k) % table.size();

            hash_node_ptr ptr = table[hsh];

            while (ptr)
            {

                if (cmp(k, key_of_type()(ptr->key)))
                {
                    return ptr;
                }
                ptr = ptr->next;
            }
            return NULL;
        }

        bool _erase(const Ky &k)
        {
            if (!_find(k))
                return false;

            size_t hsh = hash(k) % table.size();
            hash_node_ptr ptr = table[hsh];

            hash_node_ptr prev = NULL;
            while (ptr)
            {
                if (cmp(key_of_type()(ptr->key), k))
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
                delete_node(ptr);
            return true;
        }

    private:
        hash_node_ptr create_node(const Key &k)
        {
            hash_node_ptr node = alloc.allocate(1);
            alloc.construct(node, k);
            return node;
        }

        void delete_node(hash_node_ptr node)
        {
            alloc.destroy(node);
            alloc.deallocate(node, 1);
        }

    public:
        void clear()
        {
            for (size_t i = 0; i < table.size(); ++i)
            {
                hash_node_ptr cur = table[i];
                hash_node_ptr next = NULL;
                while (cur)
                {
                    next = cur->next;
                    delete_node(cur);
                    cur = next;
                }
                table[i] = NULL;
            }

            _max_load_factor = 1.0;
            sz = 0;
        }

        hash_table_self &operator=(const hash_table_self &oth)
        {

            if (&oth == this)
                return *this;

            clear();

            for (size_t i = 0; i < oth.table.size(); ++i)
            {
                hash_node_ptr cur = oth.table[i];
                // hash_node_ptr next = NULL;
                while (cur)
                {
                    _insert(cur->key);
                    cur = cur->next;
                }
            }
            return *this;
        }

        ~hash_table()
        {
            clear();
            
        }

        explicit hash_table(size_type bucket_count = 13,
                            const Hash &hash = Hash(),
                            const key_equal &equal = key_equal(),
                            const allocator_type &alloc = allocator_type()) : cmp(equal), hash(hash),
                                                                              alloc(alloc)

        {
            sz = 0;
            _max_load_factor = 1.0;
            table.resize(bucket_count, NULL);
        }

        explicit hash_table ( const allocator_type& alloc ) : alloc(alloc)
        {
            sz = 0;
            _max_load_factor = 1.0;
            table.resize(13, NULL);
        }

        template <class InputIt>
        hash_table(InputIt first, InputIt last,
                   size_type bucket_count = 13,
                   const Hash &hash = Hash(),
                   const key_equal &equal = key_equal(),
                   const allocator_type &alloc = allocator_type()) : hash(hash), cmp(equal),
                                                                     alloc(alloc)

        {
            _max_load_factor = 1.0;
            sz = 0;
            table.resize(bucket_count, NULL);
            insert(first, last);
        }

        hash_table(const hash_table &other)
        {
            _max_load_factor = 1.0;
            sz = 0;
            *this = other;
        }

        hash_table(const hash_table &other, const allocator_type &alloc) : alloc(alloc)
        {
            _max_load_factor = 1.0;
            sz = 0;
            *this = other;
        }

        // Capacity
        bool empty() const
        {
            return !sz;
        }

        size_type size() const
        {
            return sz;
        }

        // Lookup

        size_type max_size() const
        {
            return size_type(-1);
        }

        size_type count(const Ky &key) const
        {
            size_t ans = 0;
            if (empty())
                return ans;

            // size_t hsh = hash((key) )% table.size();
            // hash_node_ptr ptr = table[hsh];
            iterator it = find(key);
            while (it != end())
            {
                if (cmp(key, key_of_type()(it.node->key)))
                {
                    ans += 1;
                    if (Unique)
                        return ans;
                }
                ++it;
            }
            return ans;
        }

        iterator find(const Ky &key)
        {
            hash_node_ptr ans = _find(key);
            return iterator(ans, this);
        }

        const_iterator find(const Ky &key) const
        {
            hash_node_ptr ans = _find(key);
            return const_iterator(ans, this);
        }

    private:
        ft::pair<hash_node_ptr, hash_node_ptr>
        _equal_range(const Ky &key)
        {
            hash_node_ptr start = _find(key);

            if (!start)
                return ft::make_pair(start, start);

            if (Unique)
                return ft::make_pair(start, start->next);

            iterator it = find(key);
            iterator fin = it;
            while (fin.node && cmp(key_of_type()(fin.node->key), key))
                fin++;

            return ft::make_pair(it.node, fin.node);
        }

    public:
        ft::pair<iterator, iterator>
        equal_range(const Ky &key)
        {
            ft::pair<hash_node_ptr, hash_node_ptr> _ans = _equal_range(key);
            return ft::make_pair(iterator(_ans.first, this), iterator(_ans.second, this));
        }

        ft::pair<const_iterator, const_iterator>
        equal_range(const Ky &key) const
        {
            ft::pair<hash_node_ptr, hash_node_ptr> _ans = _equal_range(key);
            return ft::make_pair(const_iterator(_ans.first, this), const_iterator(_ans.second, this));
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
                ft::vector<hash_node_ptr> n_table(next_prime(count));
                _copy(table, n_table);
                table.swap(n_table);
            }
        }

        float load_factor() const
        {
            return _max_load_factor;
        }

        private:
        int ceil(float num) 
        {
            int inum = (int)num;
            if (num < 0 || num == (float)inum) {
                return inum;
            }
            return inum + 1;
        }
        public:
        void reserve(size_type count) // calls ceil rehash;
        {
            rehash(this->ceil(count / max_load_factor()));
        }

        // modifiers

        ft::pair<iterator, bool> insert(const value_type &value)
        {
            return _insert(value);
        }

        private:
        iterator insert_(const_iterator hint, const value_type &value)
        {
            (void)hint;
            return _insert(value).first;
        }

        template <class InputIt>
        void insert_(InputIt first, InputIt last, typename ft::enable_if<has_iterator_category<InputIt>::value>::type * = 0)
        {
            while (first != last)
            {
                _insert(*first);
                first++;
            }
        }

        public:
          iterator insert(const_iterator hint, const value_type &value)
        {
            
            return insert_(hint, value);
        }

        template <class InputIt>
        void insert(InputIt first, InputIt last)
        {
            insert_(first, last);
        }

        iterator erase(const_iterator pos, const_iterator last)
        {

            size_t hsh = hash(key_of_type()(pos.node->key)) % table.size();

            hash_node_ptr ptr = table[hsh];
            hash_node_ptr prev = NULL;

            while (ptr && ptr != pos.node)
            {
                prev = ptr;
                ptr = ptr->next;
            }

            while (ptr && ptr != last.node) // first bucket have pos
            {

                hash_node_ptr next = ptr->next;
                if (prev)
                    prev->next = next;
                else
                    table[hsh] = next;
                delete_node(ptr);
                sz--;
                ptr = next;
            }

            hsh++;
            if (last == end())
            {
                while (hsh < table.size())
                {
                    ptr = table[hsh];
                    table[hsh] = NULL;
                    while (ptr)
                    {
                        hash_node_ptr next = ptr->next;
                        delete_node(ptr);
                        sz--;
                        ptr = next;
                    }
                    ++hsh;
                }
            }
            else // even if i am using more code i understand nice in this way
            {

                while (ptr != last.node && hsh < table.size())
                {
                    ptr = table[hsh];
                    while (ptr && ptr != last.node)
                    {
                        table[hsh] = ptr->next;

                        delete_node(ptr);
                        sz--;
                        ptr = table[hsh];
                    }
                    if (ptr == last.node)
                        break;
                    ++hsh;
                }
            }
            return last;
        }

        iterator erase(iterator pos)
        {
            if (pos == end())
                return pos;
            iterator _start = pos++;
            // while (_start++ != pos)
            // {
            //     std::cerr << "YYY\n";
            // }
            return erase(_start, pos);
        }

        size_type erase(const Ky &key)
        {
            bool removed = true;
            size_type ans = 0;
            while (removed)
            {
                removed = _erase(key);
                ans += removed;
            }
            return ans;
        }

        void swap(hash_table &other)
        {
            table.swap(other.table);
            ft::swap(sz, other.sz);
            ft::swap(cmp, other.cmp);
            ft::swap(hash, other.hash);
            ft::swap(alloc, other.alloc);
            ft::swap(allocator, other.allocator);
            // swap allocator_type too;
        }

        // Iterators
        iterator begin()
        {
            for (size_t i = 0; i < table.size(); ++i)
                if (table[i])
                    return iterator(table[i], this);
            return iterator(NULL, this);
        }

        const_iterator begin() const
        {
            return cbegin();
        }
        const_iterator cbegin() const
        {
            for (size_t i = 0; i < table.size(); ++i)
                if (table[i])
                    return const_iterator(table[i], this);
            return const_iterator(NULL, this);
        }

        iterator end()
        {
            return iterator(NULL, this);
        }

        const_iterator end() const
        {
            return const_iterator(NULL, this);
        }
        const_iterator cend()
        {
            return const_iterator(NULL, this);
        }

        // Bucket interface
        size_t bucket(const Ky &key) const
        {
            return hash((key) % table.size());
        }

        size_t bucket_count() const
        {
            return table.size();
        }
        size_type max_bucket_count() const
        {
            return size_type(-1); // todo
        }
        size_type bucket_size(size_type n) const
        {
            size_t ans = 0;
            hash_node_ptr ptr = table[n];
            while (ptr)
            {
                ans++;
                ptr = ptr->next;
            }
            return ans;
        }
        local_iterator begin(size_type n)
        {
            return local_iterator(table[n]);
        }

        const_local_iterator begin(size_type n) const
        {
            (void)n;

            return const_local_iterator(table[n]);
        }

        const_local_iterator cbegin(size_type n) const
        {
            (void)n;

            return const_local_iterator(table[n]);
        }

        local_iterator end(size_type n)
        {
            (void)n;

            return local_iterator(NULL);
        }

        const_local_iterator end(size_type n) const
        {
            (void)n;

            return const_local_iterator(NULL);
        }

        const_local_iterator cend(size_type n) const
        {
            (void)n;
            return const_local_iterator(NULL);
        }

        allocator_type get_allocator() const
        {
            return allocator; // or return alloc;
        }

        hasher hash_function() const
        {
            return hash;
        }

        key_equal key_eq() const
        {
            return cmp;
        }
    };

    template <class Key, class Hash, class KeyEqual, class Alloc>
    bool operator==(const hash_table<Key, Hash, KeyEqual, Alloc> &lhs,
                    const hash_table<Key, Hash, KeyEqual, Alloc> &rhs)
    {
        if (lhs.size() != rhs.size())
            return false;

        for (typename hash_table<Key, Hash, KeyEqual, Alloc>::iterator it = lhs.begin();
             it != lhs.end(); ++it)
        {
            if (rhs.count(*it) != lhs.count(*it))
                return false;
        }
        return true;
    }

    template <class Key, class Hash, class KeyEqual, class Alloc>
    bool operator!=(const hash_table<Key, Hash, KeyEqual, Alloc> &lhs,
                    const hash_table<Key, Hash, KeyEqual, Alloc> &rhs)
    {
        return !(lhs == rhs);
    }

}

// bucket iterator later;
#endif