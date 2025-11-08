
#include "../hpp/map.hpp"
int main()
{
    ft::map<int, int> a;
    a.insert(ft::make_pair(13, 130));
    a.insert(ft::make_pair(37, 370));

    // ft::map<int, int>::const_reverse_iterator citr = a.rbegin();
    // ft::map<int, int>::const_iterator cit = a.begin();
    // ft::map<int, int>::reverse_iterator itr = a.rbegin();
    // ft::map<int, int>::iterator it = a.begin();

    // *it = ft::make_pair(32, 320); // ❌ not allowed (read-only key)
    // but you can modify the mapped value:
    // it->second = 320;
    // itr->second = 3700; // OK, reverse iterator still gives modifiable reference
    // cit and citr are const, so these are not allowed:
    // cit->second = 999; 
    // citr->second = 999; 

    // == comparison examples:
    ft::map<int, int> b(a);
    if (a == b)
        std::cout << "a == b" << std::endl;
    else
        std::cout << "a != b" << std::endl;

    b[13] = 999;
    if (a == b)
        std::cout << "a == b" << std::endl;
    else
        std::cout << "a != b" << std::endl;

    return 0;
}
