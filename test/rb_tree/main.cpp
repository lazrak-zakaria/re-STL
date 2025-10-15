#include <iostream>
#include <set>
#include <string>
#include <cstdlib>
#include <ctime>
#include "./../../set.hpp" // your ft::set header

#include <iostream>
#include <set>
#include <string>
#include <cstdlib>
#include <ctime>
// #include "set.hpp" // your ft::set header

// helper to generate random strings
std::string random_string(size_t len) {
    static const char charset[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string s;
    s.reserve(len);
    for (size_t i = 0; i < len; ++i)
        s.push_back(charset[std::rand() % (sizeof(charset) - 1)]);
    return s;
}

int main() {
    std::srand(std::time(NULL));

    ft::set<std::string> ft_s;
    std::set<std::string> std_s;

    const int N = 1000;
    std::string values[N];

    // Fill sets with random strings
    for (int i = 0; i < N; ++i) {
        values[i] = random_string(5 + std::rand() % 5);
        ft_s.insert(values[i]);
        std_s.insert(values[i]);
    }

    bool pass = true;

    // ✅ 1. Test existing keys
    for (int i = 0; i < 100; ++i) {
        int idx = std::rand() % N;
        const std::string &key = values[idx];

        if (ft_s.count(key) != std_s.count(key)) {
            std::cout << "❌ count mismatch for existing key: " << key << "\n";
            pass = false;
            break;
        }
    }

    // ✅ 2. Test non-existing keys
    for (int i = 0; i < 100; ++i) {
        std::string key = random_string(6) + "_missing";

        if (ft_s.count(key) != std_s.count(key)) {
            std::cout << "❌ count mismatch for missing key: " << key << "\n";
            pass = false;
            break;
        }
    }

    // ✅ 3. Boundary keys
    if (ft_s.count(*std_s.begin()) != 1) {
        std::cout << "❌ count mismatch for smallest element\n";
        pass = false;
    }
    if (ft_s.count(*std_s.rbegin()) != 1) {
        std::cout << "❌ count mismatch for largest element\n";
        pass = false;
    }

    if (pass)
        std::cout << "✅ ft::set::count() matches std::set for all tests.\n";
    else
        std::cout << "❌ Some count() tests failed.\n";

    return 0;
}