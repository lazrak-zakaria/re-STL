#include <iostream>
#include <unordered_set> // or <tr1/unordered_set> in some old compilers
#include "../../unordered_set.hpp"



void test_iterate_after_erase() {
    std::cout << "\n=== Test 5: Iterate After Erase ===\n";
    ft::unordered_set<int> s;
    for (int i = 0; i < 10; ++i)
        s.insert(i);

    std::cout << "Before erase: ";
    for (ft::unordered_set<int>::iterator it = s.begin(); it != s.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";


    
    // erase even numbers
    ft::unordered_set<int>::iterator it = s.begin();
    while (it != s.end()) {

        if (*it % 2 == 0)
            it = s.erase(it);
        else
            ++it;
    }

    std::cout << "After erase: ";
    for (it = s.begin(); it != s.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n" << s.size() <<"\n";
}

int main() {

    test_iterate_after_erase();
    return 0;
}
