#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cassert>
#include "../../set.hpp"

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

// Test result tracking
int total_tests = 0;
int passed_tests = 0;

void print_test_result(const std::string& test_name, bool passed) {
    total_tests++;
    if (passed) {
        passed_tests++;
        std::cout << GREEN << "[PASS] " << RESET << test_name << std::endl;
    } else {
        std::cout << RED << "[FAIL] " << RESET << test_name << std::endl;
    }
}

bool compare_multisets(const ft::multiset<std::string>& ft_ms, const std::multiset<std::string>& std_ms) {
    if (ft_ms.size() != std_ms.size()) {
        std::cout << "  Size mismatch: ft=" << ft_ms.size() << " std=" << std_ms.size() << std::endl;
        return false;
    }
    
    ft::multiset<std::string>::const_iterator ft_it = ft_ms.begin();
    std::multiset<std::string>::const_iterator std_it = std_ms.begin();
    
    while (ft_it != ft_ms.end() && std_it != std_ms.end()) {
        if (*ft_it != *std_it) {
            std::cout << "  Content mismatch: ft=\"" << *ft_it << "\" std=\"" << *std_it << "\"" << std::endl;
            return false;
        }
        ++ft_it;
        ++std_it;
    }
    
    return ft_it == ft_ms.end() && std_it == std_ms.end();
}

void print_multiset_contents(const std::string& label, const ft::multiset<std::string>& ms) {
    std::cout << "  " << label << ": ";
    for (ft::multiset<std::string>::const_iterator it = ms.begin(); it != ms.end(); ++it) {
        std::cout << "\"" << *it << "\" ";
    }
    std::cout << "(size=" << ms.size() << ")" << std::endl;
}

// ==================== INSERTION TESTS ====================

void test_insert_single_string() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    ft_ms.insert("hello");
    std_ms.insert("hello");
    
    print_test_result("Insert single string", compare_multisets(ft_ms, std_ms));
}

void test_insert_duplicate_strings() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    for (int i = 0; i < 5; i++) {
        ft_ms.insert("duplicate");
        std_ms.insert("duplicate");
    }
    
    print_test_result("Insert duplicate strings (5 times)", compare_multisets(ft_ms, std_ms));
}

void test_insert_multiple_words() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::string words[] = {"apple", "banana", "apple", "cherry", "banana", "apple", "date", "banana"};
    for (int i = 0; i < 8; i++) {
        ft_ms.insert(words[i]);
        std_ms.insert(words[i]);
    }
    
    print_test_result("Insert multiple words with duplicates", compare_multisets(ft_ms, std_ms));
}

void test_insert_alphabetical_order() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::string words[] = {"alpha", "bravo", "charlie", "delta", "echo", "foxtrot"};
    for (int i = 0; i < 6; i++) {
        ft_ms.insert(words[i]);
        std_ms.insert(words[i]);
    }
    
    print_test_result("Insert strings in alphabetical order", compare_multisets(ft_ms, std_ms));
}

void test_insert_reverse_alphabetical_order() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::string words[] = {"zebra", "yankee", "xray", "whiskey", "victor", "uniform"};
    for (int i = 0; i < 6; i++) {
        ft_ms.insert(words[i]);
        std_ms.insert(words[i]);
    }
    
    print_test_result("Insert strings in reverse alphabetical order", compare_multisets(ft_ms, std_ms));
}

void test_insert_empty_strings() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    ft_ms.insert("");
    ft_ms.insert("");
    ft_ms.insert("nonempty");
    ft_ms.insert("");
    
    std_ms.insert("");
    std_ms.insert("");
    std_ms.insert("nonempty");
    std_ms.insert("");
    
    print_test_result("Insert empty strings", compare_multisets(ft_ms, std_ms));
}

void test_insert_similar_strings() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::string words[] = {"test", "test1", "test", "test2", "test", "test1", "test"};
    for (int i = 0; i < 7; i++) {
        ft_ms.insert(words[i]);
        std_ms.insert(words[i]);
    }
    
    print_test_result("Insert similar strings with duplicates", compare_multisets(ft_ms, std_ms));
}

void test_insert_case_sensitive() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::string words[] = {"Apple", "apple", "APPLE", "Apple", "apple"};
    for (int i = 0; i < 5; i++) {
        ft_ms.insert(words[i]);
        std_ms.insert(words[i]);
    }
    
    print_test_result("Insert case-sensitive strings", compare_multisets(ft_ms, std_ms));
}

void test_insert_with_spaces() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::string phrases[] = {"hello world", "hello world", "hello  world", "hello world", "helloworld"};
    for (int i = 0; i < 5; i++) {
        ft_ms.insert(phrases[i]);
        std_ms.insert(phrases[i]);
    }
    
    print_test_result("Insert strings with spaces", compare_multisets(ft_ms, std_ms));
}

void test_insert_special_characters() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::string special[] = {"hello!", "hello!", "hello?", "hello.", "hello!", "hello,"};
    for (int i = 0; i < 6; i++) {
        ft_ms.insert(special[i]);
        std_ms.insert(special[i]);
    }
    
    print_test_result("Insert strings with special characters", compare_multisets(ft_ms, std_ms));
}

void test_insert_long_strings() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::string long_str = "this_is_a_very_long_string_for_testing_purposes_in_the_multiset";
    for (int i = 0; i < 3; i++) {
        ft_ms.insert(long_str);
        std_ms.insert(long_str);
    }
    ft_ms.insert(long_str + "_modified");
    std_ms.insert(long_str + "_modified");
    
    print_test_result("Insert long strings", compare_multisets(ft_ms, std_ms));
}

void test_insert_range_strings() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::vector<std::string> words;
    words.push_back("red");
    words.push_back("blue");
    words.push_back("red");
    words.push_back("green");
    words.push_back("blue");
    words.push_back("red");
    
    ft_ms.insert(words.begin(), words.end());
    std_ms.insert(words.begin(), words.end());
    
    print_test_result("Insert range of strings", compare_multisets(ft_ms, std_ms));
}

void test_insert_with_hint() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    ft_ms.insert("middle");
    std_ms.insert("middle");
    
    ft::multiset<std::string>::iterator ft_it = ft_ms.begin();
    std::multiset<std::string>::iterator std_it = std_ms.begin();
    
    ft_ms.insert(ft_it, "first");
    std_ms.insert(std_it, "first");
    
    ft_ms.insert(ft_it, "zebra");
    std_ms.insert(std_it, "zebra");
    
    print_test_result("Insert with hint iterator", compare_multisets(ft_ms, std_ms));
}

void test_insert_numbers_as_strings() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::string numbers[] = {"10", "2", "10", "100", "2", "10", "20"};
    for (int i = 0; i < 7; i++) {
        ft_ms.insert(numbers[i]);
        std_ms.insert(numbers[i]);
    }
    
    print_test_result("Insert numeric strings (lexicographic order)", compare_multisets(ft_ms, std_ms));
}

void test_insert_single_characters() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::string chars[] = {"a", "b", "a", "c", "b", "a", "d"};
    for (int i = 0; i < 7; i++) {
        ft_ms.insert(chars[i]);
        std_ms.insert(chars[i]);
    }
    
    print_test_result("Insert single character strings", compare_multisets(ft_ms, std_ms));
}

// ==================== DELETION TESTS ====================

void test_erase_by_iterator() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::string words[] = {"apple", "banana", "cherry", "date"};
    for (int i = 0; i < 4; i++) {
        ft_ms.insert(words[i]);
        std_ms.insert(words[i]);
    }
    
    ft::multiset<std::string>::iterator ft_it = ft_ms.begin();
    std::multiset<std::string>::iterator std_it = std_ms.begin();
    ++ft_it; ++std_it;
    
    ft_ms.erase(ft_it);
    std_ms.erase(std_it);
    
    print_test_result("Erase by iterator", compare_multisets(ft_ms, std_ms));
}

void test_erase_by_value() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::string words[] = {"apple", "banana", "apple", "cherry", "apple", "banana"};
    for (int i = 0; i < 6; i++) {
        ft_ms.insert(words[i]);
        std_ms.insert(words[i]);
    }
    
    size_t ft_erased = ft_ms.erase("apple");
    size_t std_erased = std_ms.erase("apple");
    
    bool passed = (ft_erased == std_erased) && (ft_erased == 3) && compare_multisets(ft_ms, std_ms);
    print_test_result("Erase all occurrences by value", passed);
}

void test_erase_single_from_duplicates() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    for (int i = 0; i < 5; i++) {
        ft_ms.insert("duplicate");
        std_ms.insert("duplicate");
    }
    
    ft::multiset<std::string>::iterator ft_it = ft_ms.find("duplicate");
    std::multiset<std::string>::iterator std_it = std_ms.find("duplicate");
    
    ft_ms.erase(ft_it);
    std_ms.erase(std_it);
    
    bool passed = (ft_ms.size() == 4) && compare_multisets(ft_ms, std_ms);
    print_test_result("Erase single occurrence from duplicates", passed);
}

void test_erase_nonexistent_string() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::string words[] = {"apple", "banana", "cherry"};
    for (int i = 0; i < 3; i++) {
        ft_ms.insert(words[i]);
        std_ms.insert(words[i]);
    }
    
    size_t ft_erased = ft_ms.erase("zebra");
    size_t std_erased = std_ms.erase("zebra");
    
    bool passed = (ft_erased == std_erased) && (ft_erased == 0) && compare_multisets(ft_ms, std_ms);
    print_test_result("Erase non-existent string", passed);
}

void test_erase_range() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::string words[] = {"a", "b", "c", "d", "e", "f", "g", "h"};
    for (int i = 0; i < 8; i++) {
        ft_ms.insert(words[i]);
        std_ms.insert(words[i]);
    }
    
    ft::multiset<std::string>::iterator ft_it1 = ft_ms.begin();
    std::multiset<std::string>::iterator std_it1 = std_ms.begin();
    ++ft_it1; ++ft_it1; ++std_it1; ++std_it1;
    
    ft::multiset<std::string>::iterator ft_it2 = ft_it1;
    std::multiset<std::string>::iterator std_it2 = std_it1;
    ++ft_it2; ++ft_it2; ++ft_it2; ++std_it2; ++std_it2; ++std_it2;
    
    ft_ms.erase(ft_it1, ft_it2);
    std_ms.erase(std_it1, std_it2);
    
    print_test_result("Erase range of strings", compare_multisets(ft_ms, std_ms));
}

void test_erase_all_duplicates() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    for (int i = 0; i < 10; i++) {
        ft_ms.insert("same");
        std_ms.insert("same");
    }
    
    size_t ft_count = ft_ms.erase("same");
    size_t std_count = std_ms.erase("same");
    
    bool passed = (ft_count == std_count) && (ft_count == 10) && 
                  (ft_ms.size() == 0) && compare_multisets(ft_ms, std_ms);
    print_test_result("Erase all duplicates", passed);
}

void test_erase_empty_string() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    ft_ms.insert("");
    ft_ms.insert("");
    ft_ms.insert("word");
    std_ms.insert("");
    std_ms.insert("");
    std_ms.insert("word");
    
    size_t ft_erased = ft_ms.erase("");
    size_t std_erased = std_ms.erase("");
    
    bool passed = (ft_erased == std_erased) && compare_multisets(ft_ms, std_ms);
    print_test_result("Erase empty strings", passed);
}

void test_clear() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::string words[] = {"one", "two", "one", "three", "two", "one"};
    for (int i = 0; i < 6; i++) {
        ft_ms.insert(words[i]);
        std_ms.insert(words[i]);
    }
    
    ft_ms.clear();
    std_ms.clear();
    
    bool passed = (ft_ms.size() == 0) && compare_multisets(ft_ms, std_ms);
    print_test_result("Clear all strings", passed);
}

void test_erase_and_reinsert() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::string words[] = {"cat", "dog", "bird", "cat"};
    for (int i = 0; i < 4; i++) {
        ft_ms.insert(words[i]);
        std_ms.insert(words[i]);
    }
    
    ft_ms.erase("cat");
    std_ms.erase("cat");
    
    ft_ms.insert("cat");
    ft_ms.insert("cat");
    ft_ms.insert("cat");
    std_ms.insert("cat");
    std_ms.insert("cat");
    std_ms.insert("cat");
    
    print_test_result("Erase and reinsert strings", compare_multisets(ft_ms, std_ms));
}

void test_erase_first_string() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::string words[] = {"delta", "alpha", "charlie", "bravo"};
    for (int i = 0; i < 4; i++) {
        ft_ms.insert(words[i]);
        std_ms.insert(words[i]);
    }
    
    ft_ms.erase(ft_ms.begin());
    std_ms.erase(std_ms.begin());
    
    print_test_result("Erase first string (smallest)", compare_multisets(ft_ms, std_ms));
}

void test_mixed_operations() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    // Insert
    std::string words[] = {"red", "blue", "red", "green", "blue", "red", "yellow"};
    for (int i = 0; i < 7; i++) {
        ft_ms.insert(words[i]);
        std_ms.insert(words[i]);
    }
    
    // Erase by value
    ft_ms.erase("red");
    std_ms.erase("red");
    
    // Insert more
    ft_ms.insert("purple");
    ft_ms.insert("blue");
    std_ms.insert("purple");
    std_ms.insert("blue");
    
    // Erase by iterator
    ft::multiset<std::string>::iterator ft_it = ft_ms.find("green");
    std::multiset<std::string>::iterator std_it = std_ms.find("green");
    if (ft_it != ft_ms.end() && std_it != std_ms.end()) {
        ft_ms.erase(ft_it);
        std_ms.erase(std_it);
    }
    
    print_test_result("Mixed insert and erase operations", compare_multisets(ft_ms, std_ms));
}

void test_erase_case_sensitive() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::string words[] = {"Hello", "hello", "HELLO", "Hello"};
    for (int i = 0; i < 4; i++) {
        ft_ms.insert(words[i]);
        std_ms.insert(words[i]);
    }
    
    size_t ft_erased = ft_ms.erase("Hello");
    size_t std_erased = std_ms.erase("Hello");
    
    bool passed = (ft_erased == std_erased) && compare_multisets(ft_ms, std_ms);
    print_test_result("Erase case-sensitive strings", passed);
}

void test_large_dataset() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::string base[] = {"alpha", "beta", "gamma", "delta", "epsilon"};
    for (int i = 0; i < 100; i++) {
        std::string word = base[i % 5];
        ft_ms.insert(word);
        std_ms.insert(word);
    }
    
    // Erase some
    ft_ms.erase("alpha");
    std_ms.erase("alpha");
    
    ft_ms.erase("gamma");
    std_ms.erase("gamma");
    
    print_test_result("Large dataset with duplicates", compare_multisets(ft_ms, std_ms));
}

// ==================== QUERY TESTS ====================

void test_count_strings() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::string words[] = {"apple", "banana", "apple", "cherry", "apple"};
    for (int i = 0; i < 5; i++) {
        ft_ms.insert(words[i]);
        std_ms.insert(words[i]);
    }
    
    bool passed = (ft_ms.count("apple") == std_ms.count("apple")) &&
                  (ft_ms.count("banana") == std_ms.count("banana")) &&
                  (ft_ms.count("missing") == std_ms.count("missing"));
    
    print_test_result("Count occurrences of strings", passed);
}

void test_find_strings() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::string words[] = {"dog", "cat", "dog", "bird"};
    for (int i = 0; i < 4; i++) {
        ft_ms.insert(words[i]);
        std_ms.insert(words[i]);
    }
    
    ft::multiset<std::string>::iterator ft_it = ft_ms.find("dog");
    std::multiset<std::string>::iterator std_it = std_ms.find("dog");
    
    bool passed = (ft_it != ft_ms.end()) && (std_it != std_ms.end()) && (*ft_it == *std_it);
    passed = passed && (ft_ms.find("elephant") == ft_ms.end()) && (std_ms.find("elephant") == std_ms.end());
    
    print_test_result("Find strings in multiset", passed);
}

void test_lower_upper_bound() {
    ft::multiset<std::string> ft_ms;
    std::multiset<std::string> std_ms;
    
    std::string words[] = {"a", "c", "c", "e", "g"};
    for (int i = 0; i < 5; i++) {
        ft_ms.insert(words[i]);
        std_ms.insert(words[i]);
    }
    
    ft::multiset<std::string>::iterator ft_lb = ft_ms.lower_bound("c");
    std::multiset<std::string>::iterator std_lb = std_ms.lower_bound("c");
    
    ft::multiset<std::string>::iterator ft_ub = ft_ms.upper_bound("c");
    std::multiset<std::string>::iterator std_ub = std_ms.upper_bound("c");
    
    bool passed = (*ft_lb == *std_lb) && (*ft_ub == *std_ub);
    
    print_test_result("Lower and upper bound for strings", passed);
}

// ==================== MAIN ====================

int main() {
    std::cout << BLUE << "\n╔════════════════════════════════════════════╗\n";
    std::cout << "║  FT::MULTISET STRING TESTS                 ║\n";
    std::cout << "╚════════════════════════════════════════════╝\n" << RESET;
    
    std::cout << YELLOW << "\n========== INSERTION TESTS ==========\n" << RESET;
    test_insert_single_string();
    test_insert_duplicate_strings();
    test_insert_multiple_words();
    test_insert_alphabetical_order();
    test_insert_reverse_alphabetical_order();
    test_insert_empty_strings();
    test_insert_similar_strings();
    test_insert_case_sensitive();
    test_insert_with_spaces();
    test_insert_special_characters();
    test_insert_long_strings();
    test_insert_range_strings();
    test_insert_with_hint();
    test_insert_numbers_as_strings();
    test_insert_single_characters();
    
    std::cout << YELLOW << "\n========== DELETION TESTS ==========\n" << RESET;
    test_erase_by_iterator();
    test_erase_by_value();
    test_erase_single_from_duplicates();
    test_erase_nonexistent_string();
    test_erase_range();
    test_erase_all_duplicates();
    test_erase_empty_string();
    test_clear();
    test_erase_and_reinsert();
    test_erase_first_string();
    test_mixed_operations();
    test_erase_case_sensitive();
    test_large_dataset();
    
    std::cout << YELLOW << "\n========== QUERY TESTS ==========\n" << RESET;
    test_count_strings();
    test_find_strings();
    test_lower_upper_bound();
    
    std::cout << YELLOW << "\n╔════════════════════════════════════════════╗\n";
    std::cout << "║           TEST SUMMARY                     ║\n";
    std::cout << "╚════════════════════════════════════════════╝\n" << RESET;
    std::cout << "Total tests: " << total_tests << std::endl;
    std::cout << GREEN << "Passed: " << passed_tests << RESET << std::endl;
    std::cout << RED << "Failed: " << (total_tests - passed_tests) << RESET << std::endl;
    
    double success_rate = (double)passed_tests / total_tests * 100.0;
    std::cout << "Success rate: " << success_rate << "%" << std::endl;
    
    if (passed_tests == total_tests) {
        std::cout << GREEN << "\n✓ All tests passed successfully!\n" << RESET;
        return 0;
    } else {
        std::cout << RED << "\n✗ Some tests failed. Please review.\n" << RESET;
        return 1;
    }
}