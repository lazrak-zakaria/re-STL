

namespace ft
{

    template <
        class Category,
        class T,
        class Distance,
        class Pointer = T *,
        class Reference = T &>
    class iterator
    {
    public:
        typedef Category iterator_category;
        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
    };

    template <class T>
    class vector_iterator
        : public iterator<
              std::random_access_iterator_tag,
              T,
              long long>
    {

        private:
            pointer ptr;
        
        public:
            vector_iterator();
            vector_iterator(pointer ptr);
            ~vector_iterator();
    };
};