#include <iostream>
#include "../../vector.hpp"

#include <vector>

class m
{
public:
    // Default constructor
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
    ft::vector<m> k;
    std::vector<m> v;

 for (int i = 0; i < 5; ++i) {
        std::cout << "=== Iteration " << i+1 << " ===" << std::endl;

        v.push_back(m()); // Push a temporary object

        std::cout << "Vector size: " << v.size() << std::endl;
        std::cout << "Vector capacity: " << v.capacity() << std::endl;

        std::cout << std::endl;
    }
    return 0;
}