#include <iostream>
#include <string>
#include <ctime>
#include "../../unordered_map.hpp" // your ft::unordered_multimap
#include "../../unordered_set.hpp" // your ft::unordered_multimap
#include <unordered_map>
#include <unordered_set>
// C++98 doesn't have std::to_string, so we need to implement it
// namespace std {
//     std::string to_string(int value) {
//         char buffer[20];
//         sprintf(buffer, "%d", value);
//         return std::string(buffer);
//     }
// }

int main() {
    const int N = 100000; // number of elements
    ft::unordered_multimap<int, std::string> ft_multimap;
    std::unordered_multimap<int, std::string> std_multimap;

    std::cout << "=== unordered_multimap Test ===\n";

    // Fill multimaps with duplicate keys
    std::cout << "Inserting " << N << " elements with duplicate keys..." << std::endl;
    for (int i = 0; i < N; ++i) {
        int key = i % 1000; // Create many duplicates
        ft_multimap.insert(ft::make_pair(key, "value" + std::to_string(i)));
        std_multimap.insert(std::make_pair(key, "value" + std::to_string(i)));
    }

    // 1. Test size
    std::cout << "1. Size test: ";
    if (ft_multimap.size() == std_multimap.size())
        std::cout << "PASS (ft: " << ft_multimap.size() << ", std: " << std_multimap.size() << ")\n";
    else
        std::cout << "FAIL (ft: " << ft_multimap.size() << ", std: " << std_multimap.size() << ")\n";

    // 2. Test count (should be same for duplicate keys)
    std::cout << "2. Count test: ";
    bool count_ok = true;
    for (int i = 0; i < 100; ++i) { // Test first 100 keys
        if (ft_multimap.count(i) != std_multimap.count(i)) {
            count_ok = false;
            std::cout << "FAIL at key " << i << " (ft: " << ft_multimap.count(i) 
                      << ", std: " << std_multimap.count(i) << ")\n";
            break;
        }
    }
    if (count_ok) std::cout << "PASS\n";

    // 3. Test equal_range - using ft::pair for your implementation
    std::cout << "3. Equal_range test: ";
    bool equal_range_ok = true;
    for (int i = 0; i < 50; ++i) {
        // Use ft::pair for your implementation
        ft::pair<ft::unordered_multimap<int, std::string>::iterator, 
                 ft::unordered_multimap<int, std::string>::iterator> ft_range = ft_multimap.equal_range(i);
        
        // Use std::pair for std implementation
        std::pair<std::unordered_multimap<int, std::string>::iterator, 
                  std::unordered_multimap<int, std::string>::iterator> std_range = std_multimap.equal_range(i);
        
        // Count elements in range should be the same
        int ft_count = 0, std_count = 0;
        for (ft::unordered_multimap<int, std::string>::iterator it = ft_range.first; it != ft_range.second; ++it)
            ft_count++;
        for (std::unordered_multimap<int, std::string>::iterator it = std_range.first; it != std_range.second; ++it)
            std_count++;
            
        if (ft_count != std_count) {
            equal_range_ok = false;
            std::cout << "FAIL at key " << i << " (ft: " << ft_count << ", std: " << std_count << ")\n";
            break;
        }
        
        // Also verify that all keys in the range match the search key
        for (ft::unordered_multimap<int, std::string>::iterator it = ft_range.first; it != ft_range.second; ++it) {
            if (it->first != i) {
                equal_range_ok = false;
                std::cout << "FAIL - wrong key in range at key " << i << "\n";
                break;
            }
        }
    }
    if (equal_range_ok) std::cout << "PASS\n";

    // 4. Test erase by key (removes all elements with that key)
    std::cout << "4. Erase by key test: ";
    size_t ft_erased = ft_multimap.erase(0); // Remove all elements with key 0
    size_t std_erased = std_multimap.erase(0);
    bool erase_ok = (ft_erased == std_erased) && (ft_multimap.count(0) == std_multimap.count(0));
    std::cout << (erase_ok ? "PASS" : "FAIL") << " (erased: ft=" << ft_erased << ", std=" << std_erased << ")\n";
    // 5. Test erase by iterator
    std::cout << "5. Erase by iterator test: ";
    if (!ft_multimap.empty() && !std_multimap.empty()) {
        std::cout << ft_multimap.size() << "  " << std_multimap.size() << "\n";
        ft_multimap.erase(ft_multimap.begin());
        std_multimap.erase(std_multimap.begin());
        bool iterator_erase_ok = (ft_multimap.size() == std_multimap.size());
        std::cout << (iterator_erase_ok ? "PASS" : "FAIL") << "\n";
        std::cout << ft_multimap.size() << "  " << std_multimap.size() << "\n";

    } else {
        std::cout << "SKIP (containers empty)\n";
    }

    // 6. Test iteration and values
    std::cout << "6. Iteration test: ";
    bool iteration_ok = true;
    
    // Create temporary containers to compare distributions
    ft::unordered_multimap<int, int> ft_dist;
    std::unordered_multimap<int, int> std_dist;
    
    for (ft::unordered_multimap<int, std::string>::iterator it = ft_multimap.begin(); it != ft_multimap.end(); ++it) {
        ft_dist.insert(ft::make_pair(it->first, 1));
    }
    for (std::unordered_multimap<int, std::string>::iterator it = std_multimap.begin(); it != std_multimap.end(); ++it) {
        std_dist.insert(std::make_pair(it->first, 1));
    }
    
    iteration_ok = (ft_dist.size() == std_dist.size());
    std::cout << (iteration_ok ? "PASS" : "FAIL") << " (unique keys: ft=" << ft_dist.size() << ", std=" << std_dist.size() << ")\n";

    // 7. Test clear
    std::cout << "7. Clear test: ";
    ft_multimap.clear();
    std_multimap.clear();
    bool clear_ok = (ft_multimap.empty() && std_multimap.empty());
    std::cout << (clear_ok ? "PASS" : "FAIL") << "\n";

    // 8. Test re-insertion after clear
    std::cout << "8. Re-insertion test: ";
    for (int i = 0; i < 10; ++i) {
        ft_multimap.insert(ft::make_pair(i, "new_value" + std::to_string(i)));
        std_multimap.insert(std::make_pair(i, "new_value" + std::to_string(i)));
    }
    bool reinsert_ok = (ft_multimap.size() == std_multimap.size());
    std::cout << (reinsert_ok ? "PASS" : "FAIL") << "\n";

    // 9. Test multiple identical insertions
    std::cout << "9. Duplicate insertion test: ";
    ft_multimap.insert(ft::make_pair(999, "duplicate"));
    ft_multimap.insert(ft::make_pair(999, "duplicate"));
    std_multimap.insert(std::make_pair(999, "duplicate"));
    std_multimap.insert(std::make_pair(999, "duplicate"));
    bool duplicate_ok = (ft_multimap.count(999) == std_multimap.count(999));
    std::cout << (duplicate_ok ? "PASS" : "FAIL") << " (count: ft=" << ft_multimap.count(999) 
              << ", std=" << std_multimap.count(999) << ")\n";

    // 10. Test find (should return any element with the key, not necessarily the first)
    std::cout << "10. Find test: ";
    bool find_ok = true;
    for (int i = 0; i < 20; ++i) {
        ft::unordered_multimap<int, std::string>::iterator ft_find = ft_multimap.find(i);
        std::unordered_multimap<int, std::string>::iterator std_find = std_multimap.find(i);
        
        if ((ft_find == ft_multimap.end()) != (std_find == std_multimap.end())) {
            find_ok = false;
            break;
        }
        if (ft_find != ft_multimap.end() && std_find != std_multimap.end()) {
            if (ft_find->first != std_find->first) {
                find_ok = false;
                break;
            }
        }
    }
    std::cout << (find_ok ? "PASS" : "FAIL") << "\n";

    // 11. Performance test
    std::cout << "11. Performance test:\n";
    clock_t start, end;
    
    // Insertion performance
    ft::unordered_multimap<int, std::string> ft_perf;
    std::unordered_multimap<int, std::string> std_perf;
    
    start = clock();
    for (int i = 0; i < 10000; ++i) {
        ft_perf.insert(ft::make_pair(i % 100, "test" + std::to_string(i)));
    }
    end = clock();
    double ft_time = (double)(end - start) / CLOCKS_PER_SEC;
    
    start = clock();
    for (int i = 0; i < 10000; ++i) {
        std_perf.insert(std::make_pair(i % 100, "test" + std::to_string(i)));
    }
    end = clock();
    double std_time = (double)(end - start) / CLOCKS_PER_SEC;
    
    std::cout << "   FT time: " << ft_time << "s, STD time: " << std_time << "s\n";
    std::cout << "   Ratio: " << (ft_time / std_time) << "\n";

    std::cout << "=== Test Complete ===\n";



    std::unordered_map<int, int>::iterator t ;// = std::make_pair(4,5);
    ft::unordered_set<int>::iterator it;

    ft::unordered_map<int, int> e;// = ft::make_pair(4,5);
    ft::unordered_set<int> er;
    // er.insert(43);// = ft::make_pair(4,5);
    // vv.insert(43);// = ft::make_pair(4,5);
    // e = 5;
    // *er.begin() = 87;
    // *vv.begin() = 55;
    return 0;
}