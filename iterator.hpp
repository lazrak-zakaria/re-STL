

namespace ft
{
    template <class T>
    class vector_iterator
    {

    public:
        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef long long difference_type;
        typedef T *pointer;
        typedef T &reference;

    private:
        pointer ptr;

    public:
        vector_iterator();
        vector_iterator(pointer ptr);
        ~vector_iterator();
        
    };





    template <class T>
    vector_iterator<T>::vector_iterator() : ptr(NULL)
    {
    }

    template <class T>
    vector_iterator<T>::vector_iterator(pointer ptr) : ptr(ptr)
    {}

    template <class T>
    vector_iterator<T>::~vector_iterator()
    {}







};