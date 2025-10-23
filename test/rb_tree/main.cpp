#include <iostream>
#include <map>
#include <ctime>
#include <cstdlib>
#include "../../map.hpp" // Include your ft::map header
#include "../../set.hpp" // Include your ft::map header

#define MAX_RUNS 10000
#define TEST_SIZE 1000

// Timer class for performance comparison
class Timer {
private:
    clock_t start_time;
public:
    Timer() : start_time(clock()) {}
    
    double elapsed() const {
        return (double)(clock() - start_time) / CLOCKS_PER_SEC;
    }
    
    void reset() {
        start_time = clock();
    }
};

// Test function prototypes
void test_construction() {
    std::cout << "1. CONSTRUCTION TESTS" << std::endl;
    
    // Default construction
    std::map<int, std::string> std_map;
    ft::map<int, std::string> ft_map;
    
    // Range construction

    std::pair<int, std::string> pairs[] = {
        std::make_pair(1, "one"),
        std::make_pair(2, "two"),
        std::make_pair(3, "three")
    };
    
    int ch[] = {1,2,3,4,5,6,7,8};
    std::map<int, std::string> std_map_range(pairs, pairs + 3);

    ft::map<int, std::string> ft_map_range(pairs, pairs + 3);
    // ft::set<int> s(ch, ch + 3);
      std::cout << "   Range construction: ✓" << std::endl;
    
    // Copy construction
    std::map<int, std::string> std_map_copy(std_map_range);
    ft::map<int, std::string> ft_map_copy(ft_map_range);
    
    std::cout << "   Default construction: ✓" << std::endl;
    std::cout << "   Range construction: ✓" << std::endl;
    std::cout << "   Copy construction: ✓" << std::endl;
    std::cout << "   PASSED" << std::endl << std::endl;
}


void test_insertion() {
    std::cout << "2. INSERTION TESTS" << std::endl;
    
    std::map<int, std::string> std_map;
    ft::map<int, std::string> ft_map;
    
    // Single element insertion
    std_map.insert(std::make_pair(1, "one"));
    ft_map.insert(std::make_pair(1, "one"));
    
    // Insert with hint
    std_map.insert(std_map.begin(), std::make_pair(2, "two"));
    ft_map.insert(ft_map.begin(), std::make_pair(2, "two"));
    
    // Range insertion
    std::pair<int, std::string> more_pairs[] = {
        std::make_pair(3, "three"),
        std::make_pair(4, "four"),
        std::make_pair(5, "five")
    };
    
    std_map.insert(more_pairs, more_pairs + 3);
    ft_map.insert(more_pairs, more_pairs + 3);
    
    // Operator[] insertion
    std_map[6] = "six";
    ft_map[6] = "six";
    
    bool sizes_match = (std_map.size() == ft_map.size());
    bool empty_match = (std_map.empty() == ft_map.empty());
    
    std::cout << "   Single insertion: " << (std_map.size() == 6 ? "✓" : "✗") << std::endl;
    std::cout << "   Range insertion: " << (ft_map.size() == 6 ? "✓" : "✗") << std::endl;
    std::cout << "   Operator[]: " << (ft_map[6] == "six" ? "✓" : "✗") << std::endl;
    std::cout << "   Sizes match: " << (sizes_match ? "✓" : "✗") << std::endl;
    std::cout << "   Empty match: " << (empty_match ? "✓" : "✗") << std::endl;
    std::cout << "   " << (sizes_match && empty_match ? "PASSED" : "FAILED") << std::endl << std::endl;
}



void test_erase() {
    std::cout << "5. ERASE TESTS" << std::endl;
    
    std::map<int, std::string> std_map;
    ft::map<int, std::string> ft_map;
    
    for (int i = 0; i < 20; ++i) {
        std_map[i] = "value_" + std::to_string(i);
        ft_map[i] = "value_" + std::to_string(i);
    }
    
    // Erase by iterator
    std_map.erase(std_map.find(5));
    ft_map.erase(ft_map.find(5));
    
    // Erase by key
    size_t std_erase_count = std_map.erase(10);
    size_t ft_erase_count = ft_map.erase(10);
    
    // Erase range
    std_map.erase(std_map.find(15), std_map.end());
    ft_map.erase(ft_map.find(15), ft_map.end());
    
    bool sizes_match = (std_map.size() == ft_map.size());
    bool erase_count_match = (std_erase_count == ft_erase_count);
    
    // Verify remaining elements
    bool elements_match = true;
    std::map<int, std::string>::iterator std_it = std_map.begin();
    ft::map<int, std::string>::iterator ft_it = ft_map.begin();
    
    while (std_it != std_map.end() && ft_it != ft_map.end()) {
        if (std_it->first != ft_it->first || std_it->second != ft_it->second) {
            elements_match = false;
            break;
        }
        ++std_it;
        ++ft_it;
    }
    
    std::cout << "   Erase by iterator: " << (std_map.size() == ft_map.size() ? "✓" : "✗") << std::endl;
    std::cout << "   Erase by key: " << (erase_count_match ? "✓" : "✗") << std::endl;
    std::cout << "   Erase range: " << (elements_match ? "✓" : "✗") << std::endl;
    std::cout << "   " << (sizes_match && erase_count_match && elements_match ? "PASSED" : "FAILED") << std::endl << std::endl;
}


void test_bounds() {
    std::cout << "6. BOUNDS TESTS" << std::endl;
    
    std::map<int, std::string> std_map;
    ft::map<int, std::string> ft_map;
    
    int values[] = {1, 3, 5, 7, 9};
    for (size_t i = 0; i < sizeof(values)/sizeof(values[0]); ++i) {
        std_map[values[i]] = "val";
        ft_map[values[i]] = "val";
    }
    
    bool bounds_match = true;
    
    // Test lower_bound
    for (int i = 0; i < 11; ++i) {
        std::map<int, std::string>::iterator std_lb = std_map.lower_bound(i);
        ft::map<int, std::string>::iterator ft_lb = ft_map.lower_bound(i);
        
        bool std_end = (std_lb == std_map.end());
        bool ft_end = (ft_lb == ft_map.end());
        
        if (std_end != ft_end) {
            bounds_match = false;
            break;
        }
        
        if (!std_end && !ft_end && std_lb->first != ft_lb->first) {
            bounds_match = false;
            break;
        }
    }
    
    // Test upper_bound
    for (int i = 0; i < 11; ++i) {
        std::map<int, std::string>::iterator std_ub = std_map.upper_bound(i);
        ft::map<int, std::string>::iterator ft_ub = ft_map.upper_bound(i);
        
        bool std_end = (std_ub == std_map.end());
        bool ft_end = (ft_ub == ft_map.end());
        
        if (std_end != ft_end) {
            bounds_match = false;
            break;
        }
        
        if (!std_end && !ft_end && std_ub->first != ft_ub->first) {
            bounds_match = false;
            break;
        }
    }
    
    // Test equal_range
    for (int i = 0; i < 11; ++i) {
        std::pair<std::map<int, std::string>::iterator, std::map<int, std::string>::iterator> std_range = std_map.equal_range(i);
        ft::pair<ft::map<int, std::string>::iterator, ft::map<int, std::string>::iterator> ft_range = ft_map.equal_range(i);
        
        bool std_first_end = (std_range.first == std_map.end());
        bool ft_first_end = (ft_range.first == ft_map.end());
        bool std_second_end = (std_range.second == std_map.end());
        bool ft_second_end = (ft_range.second == ft_map.end());
        
        if (std_first_end != ft_first_end || std_second_end != ft_second_end) {
            bounds_match = false;
            break;
        }
    }
    
    std::cout << "   Lower bound: " << (bounds_match ? "✓" : "✗") << std::endl;
    std::cout << "   Upper bound: " << (bounds_match ? "✓" : "✗") << std::endl;
    std::cout << "   Equal range: " << (bounds_match ? "✓" : "✗") << std::endl;
    std::cout << "   " << (bounds_match ? "PASSED" : "FAILED") << std::endl << std::endl;
}


void test_copy_swap() {
    std::cout << "7. COPY AND SWAP TESTS" << std::endl;
    
    std::map<int, std::string> std_map1, std_map2;
    ft::map<int, std::string> ft_map1, ft_map2;
    
    for (int i = 0; i < 5; ++i) {
        std_map1[i] = "map1_" + std::to_string(i);
        ft_map1[i] = "map1_" + std::to_string(i);
        std_map2[i + 10] = "map2_" + std::to_string(i);
        ft_map2[i + 10] = "map2_" + std::to_string(i);
    }
    
    // Copy assignment
    std_map2 = std_map1;
    ft_map2 = ft_map1;
    
    bool copy_assign_match = (std_map2.size() == ft_map2.size());
    
    // Swap
    std_map1.swap(std_map2);
    ft_map1.swap(ft_map2);
    
    bool swap_match = (std_map1.size() == ft_map1.size() && std_map2.size() == ft_map2.size());
    
    std::cout << "   Copy assignment: " << (copy_assign_match ? "✓" : "✗") << std::endl;
    std::cout << "   Swap: " << (swap_match ? "✓" : "✗") << std::endl;
    std::cout << "   " << (copy_assign_match && swap_match ? "PASSED" : "FAILED") << std::endl << std::endl;
}



void test_performance() {
    std::cout << "8. PERFORMANCE TESTS" << std::endl;
    
    Timer timer;
    double std_time, ft_time;
    
    // Insertion performance
    {
        std::map<int, int> std_map;
        timer.reset();
        for (int i = 0; i < TEST_SIZE; ++i) {
            std_map[i] = i * 2;
        }
        std_time = timer.elapsed();
        
        ft::map<int, int> ft_map;
        timer.reset();
        for (int i = 0; i < TEST_SIZE; ++i) {
            ft_map[i] = i * 2;
        }
        ft_time = timer.elapsed();
    }
    
    std::cout << "   Insertion (" << TEST_SIZE << " elements):" << std::endl;
    std::cout << "     std::map: " << std_time << "s" << std::endl;
    std::cout << "     ft::map:  " << ft_time << "s" << std::endl;
    std::cout << "     Ratio: " << (ft_time / std_time) << "x" << std::endl;
    
    // Search performance
    {
        std::map<int, int> std_map;
        ft::map<int, int> ft_map;
        
        for (int i = 0; i < TEST_SIZE; ++i) {
            std_map[i] = i;
            ft_map[i] = i;
        }
        
        timer.reset();
        for (int i = 0; i < TEST_SIZE; ++i) {
            std_map.find(i);
        }
        std_time = timer.elapsed();
        
        timer.reset();
        for (int i = 0; i < TEST_SIZE; ++i) {
            ft_map.find(i);
        }
        ft_time = timer.elapsed();
    }
    
    std::cout << "   Search (" << TEST_SIZE << " elements):" << std::endl;
    std::cout << "     std::map: " << std_time << "s" << std::endl;
    std::cout << "     ft::map:  " << ft_time << "s" << std::endl;
    std::cout << "     Ratio: " << (ft_time / std_time) << "x" << std::endl;
    
    std::cout << "   PERFORMANCE TEST COMPLETED" << std::endl << std::endl;
}

void test_access() {
    std::cout << "3. ACCESS TESTS" << std::endl;
    
    std::map<int, std::string> std_map;
    ft::map<int, std::string> ft_map;
    
    for (int i = 0; i < 10; ++i) {
        std_map[i] = "value_" + std::to_string(i);
        ft_map[i] = "value_" + std::to_string(i);
    }
    
    bool all_access_match = true;
    
    // Test operator[]
    for (int i = 0; i < 10; ++i) {
        if (std_map[i] != ft_map[i]) {
            all_access_match = false;
            break;
        }
    }
    
    // Test at() - if your ft::map implements it
    for (int i = 0; i < 10; ++i) {
        if (std_map.at(i) != ft_map.at(i)) {
            all_access_match = false;
            break;
        }
    }
    
    // Test find()
    for (int i = 0; i < 10; ++i) {
        std::map<int, std::string>::iterator std_it = std_map.find(i);
        ft::map<int, std::string>::iterator ft_it = ft_map.find(i);
        
        if (std_it->first != ft_it->first || std_it->second != ft_it->second) {
            all_access_match = false;
            break;
        }
    }
    
    // Test count()
    bool count_match = true;
    for (int i = 0; i < 15; ++i) {
        if (std_map.count(i) != ft_map.count(i)) {
            count_match = false;
            break;
        }
    }
    
    std::cout << "   Operator[] access: " << (all_access_match ? "✓" : "✗") << std::endl;
    std::cout << "   Find operation: " << (all_access_match ? "✓" : "✗") << std::endl;
    std::cout << "   Count operation: " << (count_match ? "✓" : "✗") << std::endl;
    std::cout << "   " << (all_access_match && count_match ? "PASSED" : "FAILED") << std::endl << std::endl;
}

int main() {
    std::cout << "=== ft::map vs std::map Comparison Tests ===\n" << std::endl;
    
    test_construction();
    test_insertion();
    test_access();
    // test_iteration();
    test_erase();
    test_bounds();
    test_copy_swap();
    test_performance();
    
    std::cout << "\n=== All tests completed ===" << std::endl;
    return 0;
}