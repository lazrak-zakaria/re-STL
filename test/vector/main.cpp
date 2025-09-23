#include <iostream>
#include "../../vector.hpp"

#include <vector>

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
    std::cout << "Before vector creation\n";
    ft::vector<int> v;
    for (int i = 0; i < 10; ++i)
    {
        v.insert(v.begin()+i, i);
        v[i] = i;
    }
    v.erase(v.begin()+3);
    for (int i = 0 ;  i < v.size() ; ++i)
        std::cout << v[i] << "\n";

    std::cout << "After vector creation\n";
    
    return 0;
}