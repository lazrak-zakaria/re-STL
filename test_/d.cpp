#include "../hpp/set.hpp"



int main()
{


    ft::set<int> a;
    a.insert(13);
    a.insert(37);

    ft::set<int>::const_reverse_iterator citr = a.rbegin();
    ft::set<int>::const_iterator cit = a.begin();
    ft::set<int>::reverse_iterator itr = a.rbegin();
    ft::set<int>::iterator it = a.begin();
    *it = 32;
    *itr = 32; 
    *citr = 32;
    *cit = 32;


    return 0;
}