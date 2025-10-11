#ifndef FT_HASH_TABLE_HPP
#define FT_HASH_TABLE_HPP

#include <memory>
#include <vector>
#include <utility>

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
        typedef hash_table<Key, Hash, Pred, Alloc> *hash_table_ptr;

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

        typedef Hash hasher;
        typedef Alloc allocator_type;
        typedef Pred key_equal;

    public:
        std::vector<hash_node_ptr> table;
        size_t sz = 0;
        Pred cmp;

        
        size_t next_prime(size_t p)
        {
            static const int prime_sz = 28;
            static const unsigned long primes[] = {\
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

        bool _insert(const key_type &k)
        {
            // if Unique and k exists return ;
            
            if (Unique && _find(k))
                return false;
            if (sz == table.size())
            {
                
                std::vector<hash_node_ptr> n_table(next_prime(table.size()));
                
                for (int i = 0; i < table.size(); ++i)
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
                table.swap(n_table);
            }

            size_t hsh = hasher()(k) % table.size();
            hash_node_ptr node = new hash_node<Key>(k);
            node->next = table[hsh];
            table[hsh] = node;
            ++sz;

            return true;
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
                    break;
                }
                prev = ptr;
                ptr = ptr->next;
            }
            if (ptr)
                delete ptr;

            // should i check load_factor in erase ??
        }




        size_t bucket( const Key& key ) const
        {
            return hasher()(key) % table.size();
        }

        size_t bucket_count() const
        {
            return table.size();
        }
    };

}


// bucket iterator later;
#endif