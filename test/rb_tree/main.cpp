#include <iostream>
// #include "../../rb_tree.hpp"
#include <set>


#include <vector>
using namespace std;
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
#include <chrono>
using namespace std;
using namespace std::chrono;
#include <map>
#include <cstdlib>
#include <ctime>    
int main() {
   
    map<int, int> mp;
    mp[3] = 55;
    map<int, int> :: iterator i = mp.begin();


    set<int, std::greater<int> > j ;
    for (int i = 0; i < 1000; ++i) {
        int value = i; 
        j.insert(value);
        
    }

    std::cout << *(j.upper_bound(50)) << "\n";
    return 0;
}