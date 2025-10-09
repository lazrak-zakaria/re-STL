#include <iostream>
#include "../../vector.hpp"

#include <vector>
#include <queue>
#include <set>

class m
{
public:
    // Default constructor

    int data;
    m() {
        std::cout << "Default constructor called" << std::endl;
    }

    
    // Copy constructor
    m(const m& other) {
        std::cout << "Copy constructor called" << std::endl;
    }

    // Destructor
    ~m() {
        std::cout << "Destructor called" << std::endl;
    }
};
int main()
{
    // std::cout << "Before vector creation\n";
    // ft::vector<int> v;
    // for (int i = 0; i < 10; ++i)
    // {
    //     v.insert(v.begin()+i, i);
    //     v[i] = i;
    // }
    // v.erase(v.begin()+3);
    // for (int i = 0 ;  i < v.size() ; ++i)
    //     std::cout << v[i] << "\n";


    // std::cout << "After vector creation\n";
    

    std::set<int> s = {1,2,3,45,6,7,8};

    std::priority_queue<int> p(s.begin(), s.end());
    std::cout << p.size()<<"\n";
    while (p.empty() == 0)
    {
        std::cout << p.top() << "\n";
        p.pop();
    }

    return 0;
}