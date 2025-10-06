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
    rb_tree<int> rb;

    set< int> st;


    auto start1 = high_resolution_clock::now();
    
    for (int i = 0; i < 1000; ++i) {
        int value = i; 
        rb.insert(value);
    }
    // rb.find(50000 -500);
    auto end1 = high_resolution_clock::now();

    // --- Second operation ---
    auto start2 = high_resolution_clock::now();

    for (int i = 0; i < 1000; ++i) {
        int value = i; 
        st.insert(value);
        
    }
    auto end2 = high_resolution_clock::now();

    // --- Calculate durations ---
    auto duration1 = duration_cast<microseconds>(end1 - start1).count();
    auto duration2 = duration_cast<microseconds>(end2 - start2).count();


    cout << "Operation 1 took: " << duration1 << " microseconds\n";
    cout << "Operation 2 took: " << duration2 << " microseconds\n";

    // std::srand(std::time(nullptr)); 
    // for (int i = 0; i < 50000; ++i) {
    //     int value = i; 
    //     rb.insert(value);
    // }
    // std::cout << rb.delete_node(40) << "\n";
    // rb.print();
    rb.print();


    map<int, int> mp;
    mp[3] = 55;
    map<int, int> :: iterator i = mp.begin();

    return 0;
}