#include <iostream>
#include "../../rb_tree.hpp"
#include <set>

#include <vector>
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

#include "../../set.hpp"

int main()
{

    ft::set<int> r;
    r.insert(3);
    r.print();
    ft::rb_tree<int> rb;
    rb.insert(44);
    rb.insert(445234);
    rb.insert(4);
    rb.insert(-453424);
    rb.insert(4455);

    rb.print();

    cout << (rb.find_(445234) == rb.end()) << "-------\n";
    rb.print();
    cout << rb.size() << "-------\n";
    
    return 0;
}