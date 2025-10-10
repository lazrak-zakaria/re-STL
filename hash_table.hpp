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
    public:
        typedef key key_type;
        typedef key value_type;

        typedef Hash hasher;
        typedef Alloc allocator_type;
        typedef Pred key_equal;

    private:
        typedef hash_node<Key> *hash_node_ptr;

        std::vector<hash_node_ptr> table;
        size_t sz;
        key_equal cmp;

        const int prime_sz = 28;
        const unsigned long primes[] =
            {
                53, 97, 193, 389, 769,
                1543, 3079, 6151, 12289, 24593,
                49157, 98317, 196613, 393241, 786433,
                1572869, 3145739, 6291469, 12582917, 25165843,
                50331653, 100663319, 201326611, 402653189, 805306457,
                1610612741, 3221225473, 4294967291};

        size_t next_prime(size_t p)
        {
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

            if (sz = table.size())
            {
                std::vector<hash_node_ptr> n_table(next_prime(table.size(), 0));
                
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
            hash_node_ptr node = new hash_node(k);
            node->next = table[hsh];
            table[hsh] = node;
            ++sz;

            return true;
        }

        hash_node_ptr _find(const key_type &k)
        {
            size_t hsh = hasher()(k) % table.size();

            hash_node_ptr ptr = table[hsh];

            while (ptr)
            {
                if (cmp(k, *ptr))
                    break;
                ptr = ptr->next;
            }
            return ptr;
        }
    };

}

#endif