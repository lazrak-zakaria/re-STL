
#include "../hpp/map.hpp"
#include "../hpp/set.hpp"
#include "../hpp/vector.hpp"
#include "../hpp/deque.hpp"
#include "../hpp/unordered_set.hpp"
#include "../hpp/unordered_map.hpp"
#include "../hpp/stack.hpp"
#include <vector>
#include <set>

class m
{
public:
    int *a;

    m() {
        a = new int();
    }

    // Copy constructor
    m(const m &b) {
        a = new int();
        *a = *(b.a);
    }


    m& operator=(const m &b) {
        if (this != &b) {  
            delete a;
            a = new int();
            *a = *(b.a);  
        }
        return *this;
    }
    bool operator<(const m &b) const {
        return *a < *(b.a);
    }
    ~m() {
        delete a;
    }
};


struct m_hash {
    std::size_t operator()(const m &obj) const {
        return std::hash<int>()(*(obj.a));
    }
};

// Equality function for m
struct m_equal {
    bool operator()(const m &lhs, const m &rhs) const {
        return *(lhs.a) == *(rhs.a);
    }
};


#include "../hpp/list.hpp"
#include <iostream>

#include "../hpp/list.hpp"
#include <iostream>

bool isZero(const m &obj) {
    return *(obj.a) == 0; 
}

int main() {

 ft::vector<m> myVec;

    // Fill vector
    for (int i = 0; i < 5; i++) {
        m tmp;
        *(tmp.a) = i;
        myVec.push_back(tmp);
    }

    std::cout << "Original vector:" << std::endl;
    for (size_t i = 0; i < myVec.size(); ++i) {
        std::cout << "Element " << i << ": " << *(myVec[i].a) << std::endl;
    }

    // Erase second element (index 1)
    myVec.erase(myVec.begin() + 3);

    std::cout << "After erasing element at index 1:" << std::endl;
    for (size_t i = 0; i < myVec.size(); ++i) {
        std::cout << "Element " << i << ": " << *(myVec[i].a) << std::endl;
    }

    // Erase a range: last two elements
    myVec.erase(myVec.end() - 2, myVec.end());

    std::cout << "After erasing last two elements:" << std::endl;
    for (size_t i = 0; i < myVec.size(); ++i) {
        std::cout << "Element " << i << ": " << *(myVec[i].a) << std::endl;
    }

    return 0;
}