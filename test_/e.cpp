#include "../hpp/unordered_set.hpp"
#include <unordered_set>


int main()
{

    {

        
        ft::unordered_set<int> a;
        a.insert(13);
        a.insert(37);
        
        
        ft::unordered_set<int>::const_iterator cit = a.begin();
        
        ft::unordered_set<int>::iterator it = a.begin();
        *it = 32;
        *cit = 32;
    }
    {

        
        std::unordered_set<int> a;
        a.insert(13);
        a.insert(37);
        
        std::unordered_set<int>::const_iterator cit = a.begin();

        std::unordered_set<int>::iterator it = a.begin();
        *it = 32;
        *cit = 32;
    }

    return 0;
}