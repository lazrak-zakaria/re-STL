#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP



#include "./ft.hpp"

template <typename T, class Alloc>
class ft::vector
{
    private:
        typedef T value_type;
        typedef Alloc allocator_type;

        typedef size_t size_type;

        typedef typename allocator_type::reference  reference ;
        typedef typename allocator_type::const_reference  const_reference ;

         
        value_type* head;
        size_type   size;
        size_type   capacity;
        allocator_type  allocator;

    public:
        T pub;

        explicit vector (const allocator_type& alloc = allocator_type()):
            head(NULL), size(0), capacity(0)
        {

        }


        void push_back (const value_type& val)
        {
            if (!head){
                head = allocator.allocate(2);
                capacity = 2;
            }
            if (size == capacity){
                value_type* temp = head;
                capacity *= 2;
                head = allocator.allocate(capacity);
                for (int i = 0 ; i < size; ++i)
                    head[i] = temp[i];
                allocator.deallocate(temp, size);
            }
            head[size] = val;
            ++size;
        }


        reference front()
        {
            return head[0];
        }

        void resize (size_type n, value_type val = value_type())
        {
            
        }

        void print(){
            for (int i = 0 ; i < size; ++i)
                std::cout<< head[i] << " ";
            std::cout << "\n";
        }
};



#endif
