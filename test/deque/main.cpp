#include <iostream>


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
#include <vector>

#include "../../deque.hpp"
#include <deque>
int main()
{
ft::deque<int> ft_t;
    std::deque<int> std_t;

    // Fill deques with initial data
    for (int i = 0; i < 323232; ++i) {
        ft_t.push_front(i);
        std_t.push_front(i);
    }

    // Single-element insert at position 5
    ft::deque<int>::iterator ft_it = ft_t.insert(ft_t.begin() + 5, 100);
    std::deque<int>::iterator std_it = std_t.insert(std_t.begin() + 5, 100);

    // Compare resulting iterators
    if (*ft_it == *std_it)
        std::cout << "✅ iterator points to inserted element correctly\n";
    else
        std::cout << "❌ iterator mismatch\n";

    // Compare sizes
    if (ft_t.size() == std_t.size())
        std::cout << "✅ size matches\n";
    else
        std::cout << "❌ size mismatch: ft=" << ft_t.size() << ", std=" << std_t.size() << "\n";

    // Compare full contents
    bool ok = true;
    ft::deque<int>::iterator it1 = ft_t.begin();
    std::deque<int>::iterator it2 = std_t.begin();
    size_t idx = 0;

    while (it1 != ft_t.end() ) {
        if (*it1 != *it2) {
            std::cout << "Mismatch at index " << idx << ": ft=" << *it1 << ", std=" << *it2 << "\n";
            ok = false;
        }
        ++it1; ++it2; ++idx;
        if (it1 == ft_t.end() ) std::cout << "HHH\n";
    }

    if (ok)
        std::cout << "✅ insert(begin+5, value) works correctly\n";
    else
        std::cout << "❌ content mismatch found\n";

    // Print resulting deque
    // std::cout << "\nft::deque content:\n";
    // for (auto &v : ft_t) std::cout << v << " ";
    // std::cout << "\nstd::deque content:\n";
    // for (auto &v : std_t) std::cout << v << " ";
    std::cout << std::endl;
    return 0;
}