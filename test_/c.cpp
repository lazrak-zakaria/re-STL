#include "../hpp/list.hpp"
#include <list>


int main()
{


    ft::list<int> a;
    a.push_back(13);
    a.push_back(37);

    ft::list<int>::const_reverse_iterator itr = a.rbegin();
    ft::list<int>::const_iterator it = a.begin();
    *it = 32;
    *itr = 32; 
    std::list<int>::iterator itt;

    return 0;
}