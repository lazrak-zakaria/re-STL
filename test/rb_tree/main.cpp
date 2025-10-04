#include <iostream>
#include "../../rb_tree.hpp"

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
#include <iostream>
#include <cstdlib>
#include <ctime>    
int main() {
    rb_tree<int> rb;

    std::srand(std::time(nullptr)); 
    for (int i = 0; i < 50; ++i) {
        int value = std::rand() % 100; 
        rb.insert(value);
    }

    rb.print();
    std::cout << rb.hei() << "\n";
    return 0;
}