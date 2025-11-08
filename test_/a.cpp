#include "../hpp/deque.hpp"
#include <deque>



int main()
{


{    ft::deque<int> a;
    a.push_back(13);
    a.push_back(37);

    ft::deque<int>::const_reverse_iterator itr = a.rbegin();
    ft::deque<int>::const_iterator it = a.begin();
    *it = 32;
    *itr = 32;}

    std::deque<int>::iterator::;
    return 0;
}