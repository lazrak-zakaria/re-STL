#include "../hpp/vector.hpp"
#include <vector>

int main()
{

    {
        ft::vector<int> a;
        a.push_back(13);
        a.push_back(37);

        ft::vector<int>::const_reverse_iterator itr = a.rbegin();
        ft::vector<int>::const_iterator it = a.begin();
        *it = 32;
        *itr = 32;
    }

    return 0;
}