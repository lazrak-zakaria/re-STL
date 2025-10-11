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
    

    std::vector<float> a;
    float h = 50;
    a.push_back(h);
    a.push_back(h);
    a.push_back(h);
    a.push_back(h);
    a.push_back(h);
    std::cout << a[0] << "\n";
    std::cout << sizeof(k()) << "\n";

    int b[] = {1,2,3,4,5,6,7,8};
    a.insert(a.begin()+3,2,  2);
    std::vector<float>::iterator it = a.begin();
    // ft::vector<int>::iterator i2 = a.end();
    while (it != a.end())
    {
        std::cout << *it << " ";
        it++;
        /* code */
    }
    
    std::cout <<  "\n";
    std::pair< const int , int> vv = {1,2};
    vv.second = 7;

    return 0;
}