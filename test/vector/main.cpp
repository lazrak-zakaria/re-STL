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
    std::vector<m> v;
    v.insert(v.begin(), m());
    v[0].data = 78;
    std::cout << v[0].data << "\n";
    std::cout << "After vector creation\n";
    
    return 0;
}