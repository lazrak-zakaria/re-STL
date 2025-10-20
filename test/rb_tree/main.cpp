#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "./../../map.hpp" // your ft::multimap header

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
    bool pass = true;

    // ✅ 1. Test insert - allowing duplicates
    std::cout << "Testing insert with duplicate keys...\n";
    {
        ft::multimap<int, std::string> ft_mm;
        std::multimap<int, std::string> std_mm;

        // Insert multiple values with same key
        ft_mm.insert(std::make_pair(1, "first"));
        ft_mm.insert(std::make_pair(1, "second"));
        ft_mm.insert(std::make_pair(1, "third"));
        ft_mm.insert(std::make_pair(2, "value"));
        
        std_mm.insert(std::make_pair(1, "first"));
        std_mm.insert(std::make_pair(1, "second"));
        std_mm.insert(std::make_pair(1, "third"));
        std_mm.insert(std::make_pair(2, "value"));

        if (ft_mm.size() != std_mm.size()) {
            std::cout << "❌ insert duplicate keys size mismatch (ft: " << ft_mm.size() 
                      << ", std: " << std_mm.size() << ")\n";
            pass = false;
        }

        // Count occurrences of key 1
        if (ft_mm.count(1) != std_mm.count(1) || ft_mm.count(1) != 3) {
            std::cout << "❌ count mismatch for duplicate keys\n";
            pass = false;
        }
    }

    // ✅ 2. Test range insert
    std::cout << "Testing range insert...\n";
    {
        std::vector<std::pair<int, std::string> > data;
        for (int i = 0; i < 50; ++i) {
            int key = std::rand() % 20; // intentionally limited range for duplicates
            std::string value = random_string(4);
            data.push_back(std::make_pair(key, value));
        }

        ft::multimap<int, std::string> ft_mm;
        std::multimap<int, std::string> std_mm;

        ft_mm.insert(data.begin(), data.end());
        std_mm.insert(data.begin(), data.end());

        if (ft_mm.size() != std_mm.size()) {
            std::cout << "❌ range insert size mismatch (ft: " << ft_mm.size() 
                      << ", std: " << std_mm.size() << ")\n";
            pass = false;
        }

        // Verify content by checking each key's count
        for (int key = 0; key < 20; ++key) {
            if (ft_mm.count(key) != std_mm.count(key)) {
                std::cout << "❌ range insert count mismatch for key " << key << "\n";
                pass = false;
                break;
            }
        }
    }

    // ✅ 3. Test count
    std::cout << "Testing count...\n";
    {
        ft::multimap<int, std::string> ft_mm;
        std::multimap<int, std::string> std_mm;

        // Insert known duplicates
        for (int i = 0; i < 5; ++i) {
            ft_mm.insert(std::make_pair(10, random_string(3)));
            std_mm.insert(std::make_pair(10, random_string(3)));
        }
        
        for (int i = 0; i < 3; ++i) {
            ft_mm.insert(std::make_pair(20, random_string(3)));
            std_mm.insert(std::make_pair(20, random_string(3)));
        }

        ft_mm.insert(std::make_pair(30, "single"));
        std_mm.insert(std::make_pair(30, "single"));

        if (ft_mm.count(10) != std_mm.count(10) || ft_mm.count(10) != 5) {
            std::cout << "❌ count(10) mismatch\n";
            pass = false;
        }

        if (ft_mm.count(20) != std_mm.count(20) || ft_mm.count(20) != 3) {
            std::cout << "❌ count(20) mismatch\n";
            pass = false;
        }

        if (ft_mm.count(30) != std_mm.count(30) || ft_mm.count(30) != 1) {
            std::cout << "❌ count(30) mismatch\n";
            pass = false;
        }

        if (ft_mm.count(999) != std_mm.count(999) || ft_mm.count(999) != 0) {
            std::cout << "❌ count(nonexistent) mismatch\n";
            pass = false;
        }
    }

    // ✅ 4. Test find - returns first occurrence (don't check value order)
    std::cout << "Testing find...\n";
    {
        ft::multimap<int, std::string> ft_mm;
        std::multimap<int, std::string> std_mm;

        ft_mm.insert(std::make_pair(5, "A"));
        ft_mm.insert(std::make_pair(5, "B"));
        ft_mm.insert(std::make_pair(5, "C"));

        std_mm.insert(std::make_pair(5, "A"));
        std_mm.insert(std::make_pair(5, "B"));
        std_mm.insert(std::make_pair(5, "C"));

        ft::multimap<int, std::string>::iterator ft_it = ft_mm.find(5);
        std::multimap<int, std::string>::iterator std_it = std_mm.find(5);

        if (ft_it == ft_mm.end() || std_it == std_mm.end()) {
            std::cout << "❌ find returned end() for existing key\n";
            pass = false;
        } else if (ft_it->first != std_it->first) {
            // Only check key, not value (since order might differ in C++98)
            std::cout << "❌ find returned wrong key\n";
            pass = false;
        }

        // Find non-existent
        if ((ft_mm.find(999) == ft_mm.end()) != (std_mm.find(999) == std_mm.end())) {
            std::cout << "❌ find(nonexistent) behavior mismatch\n";
            pass = false;
        }
    }

    // ✅ 5. Test equal_range with duplicates
    std::cout << "Testing equal_range...\n";
    {
        ft::multimap<int, std::string> ft_mm;
        std::multimap<int, std::string> std_mm;

        // Insert duplicates
        ft_mm.insert(std::make_pair(10, "one"));
        ft_mm.insert(std::make_pair(10, "two"));
        ft_mm.insert(std::make_pair(10, "three"));
        ft_mm.insert(std::make_pair(15, "other"));

        std_mm.insert(std::make_pair(10, "one"));
        std_mm.insert(std::make_pair(10, "two"));
        std_mm.insert(std::make_pair(10, "three"));
        std_mm.insert(std::make_pair(15, "other"));

        ft::pair<ft::multimap<int, std::string>::iterator,
                 ft::multimap<int, std::string>::iterator> ft_range = ft_mm.equal_range(10);
        std::pair<std::multimap<int, std::string>::iterator,
                  std::multimap<int, std::string>::iterator> std_range = std_mm.equal_range(10);

        // Count elements in range
        size_t ft_count = 0;
        size_t std_count = 0;
        
        for (ft::multimap<int, std::string>::iterator it = ft_range.first; 
             it != ft_range.second; ++it) {
            ft_count++;
        }
        
        for (std::multimap<int, std::string>::iterator it = std_range.first; 
             it != std_range.second; ++it) {
            std_count++;
        }

        if (ft_count != std_count || ft_count != 3) {
            std::cout << "❌ equal_range count mismatch (ft: " << ft_count 
                      << ", std: " << std_count << ")\n";
            pass = false;
        }

        // Check that all elements in range have the correct key
        for (ft::multimap<int, std::string>::iterator it = ft_range.first; 
             it != ft_range.second; ++it) {
            if (it->first != 10) {
                std::cout << "❌ equal_range contains wrong key\n";
                pass = false;
                break;
            }
        }
    }

    // ✅ 6. Test lower_bound and upper_bound with duplicates
    std::cout << "Testing lower_bound and upper_bound...\n";
    {
        ft::multimap<int, std::string> ft_mm;
        std::multimap<int, std::string> std_mm;

        for (int i = 0; i < 100; ++i) {
            int key = std::rand() % 30;
            std::string value = random_string(3);
            ft_mm.insert(std::make_pair(key, value));
            std_mm.insert(std::make_pair(key, value));
        }

        for (int key = 0; key < 35; ++key) {
            ft::multimap<int, std::string>::iterator ft_lb = ft_mm.lower_bound(key);
            std::multimap<int, std::string>::iterator std_lb = std_mm.lower_bound(key);

            bool ft_lb_end = (ft_lb == ft_mm.end());
            bool std_lb_end = (std_lb == std_mm.end());

            if (ft_lb_end != std_lb_end) {
                std::cout << "❌ lower_bound end() mismatch for key " << key << "\n";
                pass = false;
                break;
            }

            if (!ft_lb_end && ft_lb->first < key) {
                std::cout << "❌ lower_bound result < key for key " << key << "\n";
                pass = false;
                break;
            }

            ft::multimap<int, std::string>::iterator ft_ub = ft_mm.upper_bound(key);
            std::multimap<int, std::string>::iterator std_ub = std_mm.upper_bound(key);

            bool ft_ub_end = (ft_ub == ft_mm.end());
            bool std_ub_end = (std_ub == std_mm.end());

            if (ft_ub_end != std_ub_end) {
                std::cout << "❌ upper_bound end() mismatch for key " << key << "\n";
                pass = false;
                break;
            }

            if (!ft_ub_end && ft_ub->first <= key) {
                std::cout << "❌ upper_bound result <= key for key " << key << "\n";
                pass = false;
                break;
            }
        }
    }

    // ✅ 7. Test erase single element
    std::cout << "Testing erase single element...\n";
    {
        ft::multimap<int, std::string> ft_mm;
        std::multimap<int, std::string> std_mm;

        ft_mm.insert(std::make_pair(1, "A"));
        ft_mm.insert(std::make_pair(1, "B"));
        ft_mm.insert(std::make_pair(1, "C"));
        ft_mm.insert(std::make_pair(2, "X"));

        std_mm.insert(std::make_pair(1, "A"));
        std_mm.insert(std::make_pair(1, "B"));
        std_mm.insert(std::make_pair(1, "C"));
        std_mm.insert(std::make_pair(2, "X"));

        // Erase first occurrence of key 1
        ft::multimap<int, std::string>::iterator ft_it = ft_mm.find(1);
        std::multimap<int, std::string>::iterator std_it = std_mm.find(1);

        ft_mm.erase(ft_it);
        std_mm.erase(std_it);

        if (ft_mm.size() != std_mm.size() || ft_mm.size() != 3) {
            std::cout << "❌ erase single element size mismatch\n";
            pass = false;
        }

        if (ft_mm.count(1) != std_mm.count(1) || ft_mm.count(1) != 2) {
            std::cout << "❌ erase single element count mismatch\n";
            pass = false;
        }
    }

    // ✅ 8. Test erase by key (removes all occurrences)
    std::cout << "Testing erase by key...\n";
    {
        ft::multimap<int, std::string> ft_mm;
        std::multimap<int, std::string> std_mm;

        ft_mm.insert(std::make_pair(5, "A"));
        ft_mm.insert(std::make_pair(5, "B"));
        ft_mm.insert(std::make_pair(5, "C"));
        ft_mm.insert(std::make_pair(6, "X"));

        std_mm.insert(std::make_pair(5, "A"));
        std_mm.insert(std::make_pair(5, "B"));
        std_mm.insert(std::make_pair(5, "C"));
        std_mm.insert(std::make_pair(6, "X"));

        size_t ft_erased = ft_mm.erase(5);
        size_t std_erased = std_mm.erase(5);

        if (ft_erased != std_erased || ft_erased != 3) {
            std::cout << "❌ erase by key return value mismatch\n";
            pass = false;
        }

        if (ft_mm.size() != std_mm.size() || ft_mm.size() != 1) {
            std::cout << "❌ erase by key size mismatch\n";
            pass = false;
        }

        if (ft_mm.count(5) != 0 || std_mm.count(5) != 0) {
            std::cout << "❌ erase by key didn't remove all occurrences\n";
            pass = false;
        }
    }

    // ✅ 9. Test iteration order - only check that keys are sorted
    std::cout << "Testing iteration order...\n";
    {
        ft::multimap<int, int> ft_mm;
        std::multimap<int, int> std_mm;

        // Insert in specific order
        int data[][2] = {{5, 1}, {3, 2}, {5, 3}, {7, 4}, {3, 5}, {5, 6}};
        for (int i = 0; i < 6; ++i) {
            ft_mm.insert(std::make_pair(data[i][0], data[i][1]));
            std_mm.insert(std::make_pair(data[i][0], data[i][1]));
        }

        // Verify iteration produces same key sequence (values might differ in order)
        ft::multimap<int, int>::iterator ft_it = ft_mm.begin();
        std::multimap<int, int>::iterator std_it = std_mm.begin();

        while (ft_it != ft_mm.end() && std_it != std_mm.end()) {
            if (ft_it->first != std_it->first) {
                std::cout << "❌ iteration key order mismatch\n";
                pass = false;
                break;
            }
            ++ft_it;
            ++std_it;
        }

        if ((ft_it == ft_mm.end()) != (std_it == std_mm.end())) {
            std::cout << "❌ iteration length mismatch\n";
            pass = false;
        }

        // Verify counts for each key are the same
        if (ft_mm.count(3) != std_mm.count(3) || ft_mm.count(3) != 2) {
            std::cout << "❌ count for key 3 mismatch\n";
            pass = false;
        }
        if (ft_mm.count(5) != std_mm.count(5) || ft_mm.count(5) != 3) {
            std::cout << "❌ count for key 5 mismatch\n";
            pass = false;
        }
        if (ft_mm.count(7) != std_mm.count(7) || ft_mm.count(7) != 1) {
            std::cout << "❌ count for key 7 mismatch\n";
            pass = false;
        }
    }

    // ✅ 10. Test empty and clear
    std::cout << "Testing empty and clear...\n";
    {
        ft::multimap<int, std::string> ft_mm;
        std::multimap<int, std::string> std_mm;

        if (ft_mm.empty() != std_mm.empty() || !ft_mm.empty()) {
            std::cout << "❌ empty() initial state mismatch\n";
            pass = false;
        }

        ft_mm.insert(std::make_pair(1, "test"));
        std_mm.insert(std::make_pair(1, "test"));

        if (ft_mm.empty() != std_mm.empty() || ft_mm.empty()) {
            std::cout << "❌ empty() after insert mismatch\n";
            pass = false;
        }

        ft_mm.clear();
        std_mm.clear();

        if (ft_mm.empty() != std_mm.empty() || !ft_mm.empty()) {
            std::cout << "❌ empty() after clear mismatch\n";
            pass = false;
        }

        if (ft_mm.size() != 0 || std_mm.size() != 0) {
            std::cout << "❌ size after clear is not zero\n";
            pass = false;
        }
    }

    // ✅ 11. Test with string keys
    std::cout << "Testing with string keys...\n";
    {
        ft::multimap<std::string, int> ft_mm;
        std::multimap<std::string, int> std_mm;

        ft_mm.insert(std::make_pair("apple", 1));
        ft_mm.insert(std::make_pair("apple", 2));
        ft_mm.insert(std::make_pair("banana", 3));
        ft_mm.insert(std::make_pair("apple", 4));

        std_mm.insert(std::make_pair("apple", 1));
        std_mm.insert(std::make_pair("apple", 2));
        std_mm.insert(std::make_pair("banana", 3));
        std_mm.insert(std::make_pair("apple", 4));

        if (ft_mm.count("apple") != std_mm.count("apple") || ft_mm.count("apple") != 3) {
            std::cout << "❌ string key count mismatch\n";
            pass = false;
        }

        if (ft_mm.size() != std_mm.size()) {
            std::cout << "❌ string key size mismatch\n";
            pass = false;
        }

        // Verify keys are sorted correctly
        ft::multimap<std::string, int>::iterator ft_it = ft_mm.begin();
        std::multimap<std::string, int>::iterator std_it = std_mm.begin();
        
        if (ft_it->first != std_it->first) {
            std::cout << "❌ first key mismatch\n";
            pass = false;
        }
        
        ++ft_it; ++ft_it; ++ft_it; // Skip to last element
        ++std_it; ++std_it; ++std_it;
        
        if (ft_it->first != std_it->first) {
            std::cout << "❌ last key mismatch\n";
            pass = false;
        }
    }

    if (pass)
        std::cout << "✅ All multimap tests passed!\n";
    else
        std::cout << "❌ Some tests failed.\n";

    return 0;
}