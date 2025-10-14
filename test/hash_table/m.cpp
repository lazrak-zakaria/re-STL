#include <iostream>
#include <string>
#include <vector>
#include <map>  // We'll use std::map for comparison since std::unordered_map is C++11
#include <utility>

// Include your ft::unordered_map header
#include "../../unordered_map.hpp"

// Test utilities
template<typename K, typename V>
bool compare_maps(const ft::unordered_map<K, V>& ft_map, const std::map<K, V>& std_map) {
    if (ft_map.size() != std_map.size()) {
        std::cout << "Size mismatch: ft=" << ft_map.size() << ", std=" << std_map.size() << std::endl;
        return false;
    }
    
    typename ft::unordered_map<K, V>::const_iterator ft_it = ft_map.begin();
    typename std::map<K, V>::const_iterator std_it = std_map.begin();
    
    // Since ft::unordered_map doesn't guarantee order, we need to check content differently
    // We'll verify that all elements in ft_map exist in std_map and vice versa
    for (; std_it != std_map.end(); ++std_it) {
        typename ft::unordered_map<K, V>::const_iterator ft_find = ft_map.find(std_it->first);
        if (ft_find == ft_map.end() || ft_find->second != std_it->second) {
            std::cout << "Element mismatch for key " << std_it->first << std::endl;
            return false;
        }
    }
    
    // Check the other way around
    for (ft_it = ft_map.begin(); ft_it != ft_map.end(); ++ft_it) {
        typename std::map<K, V>::const_iterator std_find = std_map.find(ft_it->first);
        if (std_find == std_map.end() || std_find->second != ft_it->second) {
            std::cout << "Element mismatch for key " << ft_it->first << std::endl;
            return false;
        }
    }
    
    return true;
}

void print_test_result(const std::string& test_name, bool passed) {
    std::cout << test_name << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
}

template<typename K, typename V>
void print_ft_map(const ft::unordered_map<K, V>& map, const std::string& name) {
    std::cout << "ft::unordered_map " << name << " (" << map.size() << " elements): ";
    for (typename ft::unordered_map<K, V>::const_iterator it = map.begin(); it != map.end(); ++it) {
        std::cout << "(" << it->first << "," << it->second << ") ";
    }
    std::cout << std::endl;
}

template<typename K, typename V>
void print_std_map(const std::map<K, V>& map, const std::string& name) {
    std::cout << "std::map " << name << " (" << map.size() << " elements): ";
    for (typename std::map<K, V>::const_iterator it = map.begin(); it != map.end(); ++it) {
        std::cout << "(" << it->first << "," << it->second << ") ";
    }
    std::cout << std::endl;
}

// Test functions
void test_constructor() {
    std::cout << "=== Testing Constructors ===" << std::endl;
    
    // Default constructor
    ft::unordered_map<int, std::string> ft_map1;
    std::map<int, std::string> std_map1;
    print_test_result("Default constructor", ft_map1.size() == std_map1.size());
    
    // Range constructor
    std::vector<std::pair<int, std::string> > vec;
    vec.push_back(std::make_pair(1, "one"));
    vec.push_back(std::make_pair(2, "two"));
    vec.push_back(std::make_pair(3, "three"));
    
    ft::unordered_map<int, std::string> ft_map2(vec.begin(), vec.end());
    std::map<int, std::string> std_map2(vec.begin(), vec.end());
    print_test_result("Range constructor", compare_maps(ft_map2, std_map2));
    
    // Copy constructor
    ft::unordered_map<int, std::string> ft_map3(ft_map2);
    std::map<int, std::string> std_map3(std_map2);
    print_test_result("Copy constructor", compare_maps(ft_map3, std_map3));
    
    print_ft_map(ft_map2, "ft_map2");
    print_std_map(std_map2, "std_map2");
}

void test_assignment() {
    std::cout << "\n=== Testing Assignment ===" << std::endl;
    
    ft::unordered_map<int, std::string> ft_map1;
    std::map<int, std::string> std_map1;
    ft_map1.insert(std::make_pair(1, "one"));
    ft_map1.insert(std::make_pair(2, "two"));
    std_map1.insert(std::make_pair(1, "one"));
    std_map1.insert(std::make_pair(2, "two"));
    
    ft::unordered_map<int, std::string> ft_map2;
    std::map<int, std::string> std_map2;
    ft_map2 = ft_map1;
    std_map2 = std_map1;
    
    print_test_result("Assignment operator", compare_maps(ft_map2, std_map2));
}

void test_insert() {
    std::cout << "\n=== Testing Insert ===" << std::endl;
    
    ft::unordered_map<int, std::string> ft_map;
    std::map<int, std::string> std_map;
    
    // Test single element insert
    ft::pair<ft::unordered_map<int, std::string>::iterator, bool> ft_result1 = 
        ft_map.insert(std::make_pair(1, "one"));
    std::pair<std::map<int, std::string>::iterator, bool> std_result1 = 
        std_map.insert(std::make_pair(1, "one"));
    
    print_test_result("Single insert new element", 
                     ft_result1.second == std_result1.second && 
                     ft_result1.first->first == std_result1.first->first &&
                     ft_result1.first->second == std_result1.first->second);
    
    // Test insert duplicate
    ft::pair<ft::unordered_map<int, std::string>::iterator, bool> ft_result2 = 
        ft_map.insert(std::make_pair(1, "ONE_DUPLICATE"));
    std::pair<std::map<int, std::string>::iterator, bool> std_result2 = 
        std_map.insert(std::make_pair(1, "ONE_DUPLICATE"));
    
    print_test_result("Single insert duplicate", 
                     ft_result2.second == std_result2.second);
    
    // Test range insert
    std::vector<std::pair<int, std::string> > vec;
    vec.push_back(std::make_pair(2, "two"));
    vec.push_back(std::make_pair(3, "three"));
    vec.push_back(std::make_pair(4, "four"));
    
    ft_map.insert(vec.begin(), vec.end());
    std_map.insert(vec.begin(), vec.end());
    
    print_test_result("Range insert", compare_maps(ft_map, std_map));
    
    // Test hint insert
    ft::unordered_map<int, std::string>::iterator ft_it = ft_map.find(2);
    std::map<int, std::string>::iterator std_it = std_map.find(2);
    
    ft_map.insert(ft_it, std::make_pair(5, "five"));
    std_map.insert(std_it, std::make_pair(5, "five"));
    
    print_test_result("Hint insert", compare_maps(ft_map, std_map));
    
    print_ft_map(ft_map, "after insert");
    print_std_map(std_map, "after insert");
}

void test_erase() {
    std::cout << "\n=== Testing Erase ===" << std::endl;
    
    ft::unordered_map<int, std::string> ft_map;
    std::map<int, std::string> std_map;
    
    // Populate maps
    for (int i = 1; i <= 5; ++i) {
        ft_map.insert(std::make_pair(i, "value"));
        std_map.insert(std::make_pair(i, "value"));
    }
    
    // Test erase by key
    size_t ft_erased = ft_map.erase(3);
    size_t std_erased = std_map.erase(3);
    
    print_test_result("Erase by key return value", ft_erased == std_erased);
    print_test_result("Erase by key content", compare_maps(ft_map, std_map));
    
    // Test erase by iterator
    ft::unordered_map<int, std::string>::iterator ft_it = ft_map.find(2);
    std::map<int, std::string>::iterator std_it = std_map.find(2);
    
    if (ft_it != ft_map.end() && std_it != std_map.end()) {
        ft_map.erase(ft_it);
        std_map.erase(std_it);
        print_test_result("Erase by iterator", compare_maps(ft_map, std_map));
    }
    
    // Test erase range
    ft::unordered_map<int, std::string>::iterator ft_it1 = ft_map.find(1);
    ft::unordered_map<int, std::string>::iterator ft_it2 = ft_map.find(5);
    std::map<int, std::string>::iterator std_it1 = std_map.find(1);
    std::map<int, std::string>::iterator std_it2 = std_map.find(5);
    
    if (ft_it1 != ft_map.end() && ft_it2 != ft_map.end() &&
        std_it1 != std_map.end() && std_it2 != std_map.end()) {
        ft_map.erase(ft_it1, ft_it2);
        std_map.erase(std_it1, std_it2);
        print_test_result("Erase range", compare_maps(ft_map, std_map));
    }
}

void test_find_count() {
    std::cout << "\n=== Testing Find and Count ===" << std::endl;
    
    ft::unordered_map<int, std::string> ft_map;
    std::map<int, std::string> std_map;
    
    ft_map.insert(std::make_pair(1, "one"));
    ft_map.insert(std::make_pair(2, "two"));
    std_map.insert(std::make_pair(1, "one"));
    std_map.insert(std::make_pair(2, "two"));
    
    // Test find existing
    ft::unordered_map<int, std::string>::iterator ft_find1 = ft_map.find(1);
    std::map<int, std::string>::iterator std_find1 = std_map.find(1);
    
    print_test_result("Find existing element", 
                     ft_find1 != ft_map.end() && std_find1 != std_map.end() &&
                     ft_find1->first == std_find1->first &&
                     ft_find1->second == std_find1->second);
    
    // Test find non-existing
    ft::unordered_map<int, std::string>::iterator ft_find2 = ft_map.find(99);
    std::map<int, std::string>::iterator std_find2 = std_map.find(99);
    
    print_test_result("Find non-existing element", 
                     ft_find2 == ft_map.end() && std_find2 == std_map.end());
    
    // Test count
    size_t ft_count1 = ft_map.count(1);
    size_t ft_count2 = ft_map.count(99);
    size_t std_count1 = std_map.count(1);
    size_t std_count2 = std_map.count(99);
    
    print_test_result("Count existing element", ft_count1 == std_count1);
    print_test_result("Count non-existing element", ft_count2 == std_count2);
}

void test_iterators() {
    std::cout << "\n=== Testing Iterators ===" << std::endl;
    
    ft::unordered_map<int, std::string> ft_map;
    std::map<int, std::string> std_map;
    
    for (int i = 1; i <= 3; ++i) {
        ft_map.insert(std::make_pair(i, "value"));
        std_map.insert(std::make_pair(i, "value"));
    }
    
    // Test iterator traversal
    ft::unordered_map<int, std::string>::iterator ft_it = ft_map.begin();
    std::map<int, std::string>::iterator std_it = std_map.begin();
    
    int ft_count = 0;
    int std_count = 0;
    
    for (; ft_it != ft_map.end(); ++ft_it) ++ft_count;
    for (; std_it != std_map.end(); ++std_it) ++std_count;
    
    print_test_result("Iterator traversal count", ft_count == std_count);
    
    // Test const iterators
    const ft::unordered_map<int, std::string>& ft_const_map = ft_map;
    const std::map<int, std::string>& std_const_map = std_map;
    
    ft::unordered_map<int, std::string>::const_iterator ft_cit = ft_const_map.begin();
    std::map<int, std::string>::const_iterator std_cit = std_const_map.begin();
    
    int ft_const_count = 0;
    int std_const_count = 0;
    
    for (; ft_cit != ft_const_map.end(); ++ft_cit) ++ft_const_count;
    for (; std_cit != std_const_map.end(); ++std_cit) ++std_const_count;
    
    print_test_result("Const iterator traversal", ft_const_count == std_const_count);
}

void test_clear_swap() {
    std::cout << "\n=== Testing Clear and Swap ===" << std::endl;
    
    ft::unordered_map<int, std::string> ft_map1, ft_map2;
    std::map<int, std::string> std_map1, std_map2;
    
    ft_map1.insert(std::make_pair(1, "one"));
    ft_map1.insert(std::make_pair(2, "two"));
    std_map1.insert(std::make_pair(1, "one"));
    std_map1.insert(std::make_pair(2, "two"));
    
    ft_map2.insert(std::make_pair(3, "three"));
    std_map2.insert(std::make_pair(3, "three"));
    
    // Test swap
    ft_map1.swap(ft_map2);
    std_map1.swap(std_map2);
    
    print_test_result("Swap map1", compare_maps(ft_map1, std_map1));
    print_test_result("Swap map2", compare_maps(ft_map2, std_map2));
    
    // Test clear
    ft_map1.clear();
    std_map1.clear();
    
    print_test_result("Clear size", ft_map1.size() == std_map1.size());
    print_test_result("Clear empty", ft_map1.empty() == std_map1.empty());
}

void test_edge_cases() {
    std::cout << "\n=== Testing Edge Cases ===" << std::endl;
    
    // Test empty map operations
    ft::unordered_map<int, std::string> ft_empty;
    std::map<int, std::string> std_empty;
    
    print_test_result("Empty map find", ft_empty.find(1) == ft_empty.end());
    print_test_result("Empty map count", ft_empty.count(1) == 0);
    print_test_result("Empty map erase", ft_empty.erase(1) == 0);
    
    // Test with large number of elements
    ft::unordered_map<int, int> ft_large;
    std::map<int, int> std_large;
    
    for (int i = 0; i < 1000; ++i) {
        ft_large.insert(std::make_pair(i, i * 2));
        std_large.insert(std::make_pair(i, i * 2));
    }
    
    print_test_result("Large map size", ft_large.size() == std_large.size());
    
    // Verify some random elements
    bool large_correct = true;
    for (int i = 0; i < 100; ++i) {
        int key = i * 10;
        ft::unordered_map<int, int>::iterator ft_it = ft_large.find(key);
        std::map<int, int>::iterator std_it = std_large.find(key);
        
        if (ft_it == ft_large.end() || std_it == std_large.end() || 
            ft_it->second != std_it->second) {
            large_correct = false;
            break;
        }
    }
    print_test_result("Large map content", large_correct);
}

int main() {
    std::cout << "Starting ft::unordered_map vs std::map comparison tests\n" << std::endl;
    
    test_constructor();
    test_assignment();
    test_insert();
    test_erase();
    test_find_count();
    test_iterators();
    test_clear_swap();
    test_edge_cases();
    
    std::cout << "\nAll tests completed!" << std::endl;
    
    return 0;
}