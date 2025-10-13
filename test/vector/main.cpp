#include <iostream>
#include "../../vector.hpp"

#include <vector>
#include <queue>
#include <set>
#include <unordered_set>
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



int k();


#include <utility>
#include <set>

int main()
{


    ft::vector<int> a;
    for (int i = 0 ; i < 10; ++i)
        a.push_back(i);
    std::set<int> v;
    v.insert(4);
    ft::vector<int>::iterator it = a.begin();

    *it = 4;
    // *it = 3;
    // it[4];
    // std::cout << it[4] << "\n";
    for (int i = 0 ; i < a.size(); ++i)
        std::cout << a[i] << "\n";
    
    

    return 0;
}