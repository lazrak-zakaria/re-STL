#include <memory>

#include"hash_table.hpp"

namespace ft
{

    template<class Pair>
    struct MapKeyOfT
    {
        const typename Pair::first_type& operator()(const Pair& p) const noexcept
        {
            return p.first;
        }
    };
    
template <class Key,
          class T,
          class Hash = std::hash<Key>,
          class Pred = std::equal_to<Key>,
          class Alloc = std::allocator<std::pair<const Key, T>>>
class unordered_map : public hash_table< std::pair<const Key, T>, const Key, MapKeyOfT<std::pair<const Key, T> >, Hash, Pred, Alloc, true>
{
private:
    typedef hash_table<std::pair<const Key, T>, const Key, MapKeyOfT<std::pair<const Key, T>>, Hash, Pred, Alloc, true> hash_table_type;

public:
    explicit unordered_map(size_t bucket_count = 13,
                           const Hash &hash = Hash(),
                           const Pred &equal = Pred(),
                           const Alloc &alloc = Alloc()) : hash_table_type(bucket_count,
                                                                           hash,
                                                                           equal,
                                                                           alloc)
    {
    }

    template <class InputIt>
    unordered_map(InputIt first, InputIt last,
                  size_t bucket_count = 13,
                  const Hash &hash = Hash(),
                  const Pred &equal = Pred(),
                  const Alloc &alloc = Alloc()) : hash_table_type(first,
                                                                  last,
                                                                  bucket_count,
                                                                  hash,
                                                                  equal,
                                                                  alloc)
    {
    }

    unordered_map(const unordered_map &other) : hash_table_type(other)
    {
    }

    unordered_map(const unordered_map &other, const Alloc &alloc) : hash_table_type(other)
    {
    }

    ~unordered_map()
    {
    }
};


}


