#include <iostream>


using namespace std;
class m
{
public:
    // Default constructor

    int data;
    m()
    {
        std::cout << "Default constructor called" << std::endl;
    }

    // Copy constructor
    m(const m &other)
    {
        std::cout << "Copy constructor called" << std::endl;
    }

    // Destructor
    ~m()
    {
        std::cout << "Destructor called" << std::endl;
    }
};

#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
#include <map>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "../../deque.hpp"

int main()
{

   ft::deque<int> t;
    t.push_back(4);
    t.push_back(3);
    t.push_back(5);
    for (int i = 9; i < 24; ++i)
     t.push_front(i);
    ft::deque<int>::iterator it = t.begin();
    while (it != t.end())
    {
        std::cout << *it << "-\n";
    ++it;
    }
    return 0;
}