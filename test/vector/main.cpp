#include <iostream>
#include "../../vector.hpp"

#include <vector>

class m
{
public:
    // Default constructor
    m() {
        // std::cout << "Default constructor called" << std::endl;
    }

    // Copy constructor
    m(const m& other) {
        // std::cout << "Copy constructor called" << std::endl;
    }

    // Destructor
    ~m() {
        // std::cout << "Destructor called" << std::endl;
    }
};
int main()
{
    // ft::vector<m> v;



    std::vector<int> myvector;
    std::vector<int>::iterator it;

    it = myvector.begin();
    myvector.insert ( it , 200 );
    
    for (int i = 0 ; i < myvector.size(); ++i)
    {
        std::cout << myvector[i] << " ";

    }
    std::cout << "\n";
    return 0;
}