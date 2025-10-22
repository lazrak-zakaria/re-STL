#include <iostream>
#include <list>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include "../../../list.hpp" // Your ft::list header
#include <vector>
#include <list>
// Color codes for terminal output
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"



// Timer utility
class Timer {
    clock_t start;
public:
    Timer() : start(clock()) {}
    double elapsed() const {
        return double(clock() - start) / CLOCKS_PER_SEC * 1000.0; // ms
    }
};

// Test result tracker
struct TestResult {
    std::string name;
    bool passed;
    double ft_time;
    double std_time;
};

std::vector<TestResult> results;

void printResult(const std::string& test_name, bool passed, double ft_time, double std_time) {
    TestResult r;
    r.name = test_name;
    r.passed = passed;
    r.ft_time = ft_time;
    r.std_time = std_time;
    results.push_back(r);
    
    std::cout << (passed ? GREEN "[PASS]" : RED "[FAIL]") << RESET 
              << " " << test_name << "\n";
    std::cout << "       ft::list: " << std::fixed << std::setprecision(3) 
              << ft_time << "ms | std::list: " << std_time << "ms";
    if (std_time > 0) {
        double ratio = ft_time / std_time;
        std::cout << " (ratio: " << std::setprecision(2) << ratio << "x)";
    }
    std::cout << "\n\n";
}

template<typename T>
bool compareLists(const ft::list<T>& ft_l, const std::list<T>& std_l) {
    if (ft_l.size() != std_l.size()) {
        std::cout << "       Size mismatch: ft=" << ft_l.size() 
                  << " std=" << std_l.size() << "\n";
        return false;
    }
    
    typename ft::list<T>::const_iterator ft_it = ft_l.begin();
    typename std::list<T>::const_iterator std_it = std_l.begin();
    
    size_t pos = 0;
    while (ft_it != ft_l.end() && std_it != std_l.end()) {
        if (*ft_it != *std_it) {
            std::cout << "       Value mismatch at pos " << pos 
                      << ": ft=" << *ft_it << " std=" << *std_it << "\n";
            return false;
        }
        ++ft_it;
        ++std_it;
        ++pos;
    }
    
    return ft_it == ft_l.end() && std_it == std_l.end();
}

// Test 1: Basic insertion (push_back, push_front, insert)
void testBasicInsertion() {
    const int N = 50000;
    ft::list<int> ft_l;
    std::list<int> std_l;
    bool passed = true;
    
    Timer ft_timer;
    for (int i = 0; i < N; ++i) {
        ft_l.push_back(i);
    }
    for (int i = 0; i < N; ++i) {
        ft_l.push_front(i);
    }
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    for (int i = 0; i < N; ++i) {
        std_l.push_back(i);
    }
    for (int i = 0; i < N; ++i) {
        std_l.push_front(i);
    }
    double std_time = std_timer.elapsed();
    
    passed = compareLists(ft_l, std_l);
    
    printResult("Basic Insertion (push_back/push_front)", passed, ft_time, std_time);
}

// Test 2: Insert at position
void testInsertAtPosition() {
    const int N = 10000;
    ft::list<int> ft_l;
    std::list<int> std_l;
    bool passed = true;
    
    // Pre-fill lists
    for (int i = 0; i < 100; ++i) {
        ft_l.push_back(i);
        std_l.push_back(i);
    }
    
    Timer ft_timer;
    for (int i = 0; i < N; ++i) {
        ft::list<int>::iterator it = ft_l.begin();
        std::advance(it, ft_l.size() / 2);
        ft_l.insert(it, i * 2);
    }
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    for (int i = 0; i < N; ++i) {
        std::list<int>::iterator it = std_l.begin();
        std::advance(it, std_l.size() / 2);
        std_l.insert(it, i * 2);
    }
    double std_time = std_timer.elapsed();
    
    passed = compareLists(ft_l, std_l);
    
    printResult("Insert at Position", passed, ft_time, std_time);
}

// Test 3: Sort
void testSort() {
    const int N = 10000;
    ft::list<int> ft_l;
    std::list<int> std_l;
    bool passed = true;
    
    // Fill with random numbers
    srand(42);
    for (int i = 0; i < N; ++i) {
        int val = rand() % 1000;
        ft_l.push_back(val);
        std_l.push_back(val);
    }
    
    Timer ft_timer;
    ft_l.sort();
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    std_l.sort();
    double std_time = std_timer.elapsed();
    
    passed = compareLists(ft_l, std_l);
    
    printResult("Sort", passed, ft_time, std_time);
}

// Test 4: Splice - entire list
void testSpliceEntireList() {
    const int N = 5000;
    ft::list<int> ft_l1, ft_l2;
    std::list<int> std_l1, std_l2;
    bool passed = true;
    
    for (int i = 0; i < N; ++i) {
        ft_l1.push_back(i);
        std_l1.push_back(i);
        ft_l2.push_back(i + N);
        std_l2.push_back(i + N);
    }
    
    Timer ft_timer;
    ft::list<int>::iterator ft_it = ft_l1.begin();
    std::advance(ft_it, N / 2);
    ft_l1.splice(ft_it, ft_l2);
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    std::list<int>::iterator std_it = std_l1.begin();
    std::advance(std_it, N / 2);
    std_l1.splice(std_it, std_l2);
    double std_time = std_timer.elapsed();
    
    passed = compareLists(ft_l1, std_l1) && compareLists(ft_l2, std_l2);
    
    printResult("Splice (entire list)", passed, ft_time, std_time);
}

// Test 5: Splice - single element
void testSpliceSingleElement() {
    const int N = 5000;
    ft::list<int> ft_l1, ft_l2;
    std::list<int> std_l1, std_l2;
    bool passed = true;
    
    for (int i = 0; i < N; ++i) {
        ft_l1.push_back(i);
        std_l1.push_back(i);
        ft_l2.push_back(i + N);
        std_l2.push_back(i + N);
    }
    
    Timer ft_timer;
    ft::list<int>::iterator ft_pos = ft_l1.begin();
    ft::list<int>::iterator ft_elem = ft_l2.begin();
    std::advance(ft_elem, N / 2);
    ft_l1.splice(ft_pos, ft_l2, ft_elem);
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    std::list<int>::iterator std_pos = std_l1.begin();
    std::list<int>::iterator std_elem = std_l2.begin();
    std::advance(std_elem, N / 2);
    std_l1.splice(std_pos, std_l2, std_elem);
    double std_time = std_timer.elapsed();
    
    passed = compareLists(ft_l1, std_l1) && compareLists(ft_l2, std_l2);
    
    printResult("Splice (single element)", passed, ft_time, std_time);
}

// Test 6: Splice - range
void testSpliceRange() {
    const int N = 5000;
    ft::list<int> ft_l1, ft_l2;
    std::list<int> std_l1, std_l2;
    bool passed = true;
    
    for (int i = 0; i < N; ++i) {
        ft_l1.push_back(i);
        std_l1.push_back(i);
        ft_l2.push_back(i + N);
        std_l2.push_back(i + N);
    }
    
    Timer ft_timer;
    ft::list<int>::iterator ft_pos = ft_l1.begin();
    ft::list<int>::iterator ft_first = ft_l2.begin();
    ft::list<int>::iterator ft_last = ft_l2.begin();
    std::advance(ft_first, N / 4);
    std::advance(ft_last, 3 * N / 4);
    ft_l1.splice(ft_pos, ft_l2, ft_first, ft_last);
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    std::list<int>::iterator std_pos = std_l1.begin();
    std::list<int>::iterator std_first = std_l2.begin();
    std::list<int>::iterator std_last = std_l2.begin();
    std::advance(std_first, N / 4);
    std::advance(std_last, 3 * N / 4);
    std_l1.splice(std_pos, std_l2, std_first, std_last);
    double std_time = std_timer.elapsed();
    
    passed = compareLists(ft_l1, std_l1) && compareLists(ft_l2, std_l2);
    
    printResult("Splice (range)", passed, ft_time, std_time);
}

// Test 7: Iterator operations
void testIterators() {
    const int N = 50000;
    ft::list<int> ft_l;
    std::list<int> std_l;
    bool passed = true;
    
    for (int i = 0; i < N; ++i) {
        ft_l.push_back(i);
        std_l.push_back(i);
    }
    
    Timer ft_timer;
    int ft_sum = 0;
    for (ft::list<int>::iterator it = ft_l.begin(); it != ft_l.end(); ++it) {
        ft_sum += *it;
    }
    for (ft::list<int>::reverse_iterator rit = ft_l.rbegin(); rit != ft_l.rend(); ++rit) {
        ft_sum += *rit;
    }
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    int std_sum = 0;
    for (std::list<int>::iterator it = std_l.begin(); it != std_l.end(); ++it) {
        std_sum += *it;
    }
    for (std::list<int>::reverse_iterator rit = std_l.rbegin(); rit != std_l.rend(); ++rit) {
        std_sum += *rit;
    }
    double std_time = std_timer.elapsed();
    
    passed = (ft_sum == std_sum) && compareLists(ft_l, std_l);
    
    printResult("Iterator Operations (forward/reverse)", passed, ft_time, std_time);
}

// Test 8: Sort with custom comparator
void testSortCustomComparator() {
    const int N = 10000;
    ft::list<int> ft_l;
    std::list<int> std_l;
    bool passed = true;
    
    srand(42);
    for (int i = 0; i < N; ++i) {
        int val = rand() % 1000;
        ft_l.push_back(val);
        std_l.push_back(val);
    }
    
    Timer ft_timer;
    ft_l.sort(std::greater<int>());
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    std_l.sort(std::greater<int>());
    double std_time = std_timer.elapsed();
    
    passed = compareLists(ft_l, std_l);
    
    printResult("Sort (custom comparator - descending)", passed, ft_time, std_time);
}

// Test 9: Reverse Iterator - traversal and comparison
void testReverseIteratorTraversal() {
    const int N = 50000;
    ft::list<int> ft_l;
    std::list<int> std_l;
    bool passed = true;
    
    for (int i = 0; i < N; ++i) {
        ft_l.push_back(i);
        std_l.push_back(i);
    }
    
    Timer ft_timer;
    std::vector<int> ft_rev;
    for (ft::list<int>::reverse_iterator rit = ft_l.rbegin(); rit != ft_l.rend(); ++rit) {
        ft_rev.push_back(*rit);
    }
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    std::vector<int> std_rev;
    for (std::list<int>::reverse_iterator rit = std_l.rbegin(); rit != std_l.rend(); ++rit) {
        std_rev.push_back(*rit);
    }
    double std_time = std_timer.elapsed();
    
    // Compare reverse traversal results
    if (ft_rev.size() != std_rev.size()) {
        passed = false;
        std::cout << "       Reverse size mismatch\n";
    } else {
        for (size_t i = 0; i < ft_rev.size(); ++i) {
            if (ft_rev[i] != std_rev[i]) {
                passed = false;
                std::cout << "       Reverse value mismatch at pos " << i << "\n";
                break;
            }
        }
    }
    
    printResult("Reverse Iterator (traversal)", passed, ft_time, std_time);
}

// Test 10: Reverse Iterator - increment/decrement operations
void testReverseIteratorOperations() {
    const int N = 1000;
    ft::list<int> ft_l;
    std::list<int> std_l;
    bool passed = true;
    
    for (int i = 0; i < N; ++i) {
        ft_l.push_back(i);
        std_l.push_back(i);
    }
    
    Timer ft_timer;
    ft::list<int>::reverse_iterator ft_rit = ft_l.rbegin();
    int ft_val1 = *ft_rit;
    ++ft_rit;
    int ft_val2 = *ft_rit;
    --ft_rit;
    int ft_val3 = *ft_rit;
    ft_rit++;
    int ft_val4 = *ft_rit;
    ft_rit--;
    int ft_val5 = *ft_rit;
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    std::list<int>::reverse_iterator std_rit = std_l.rbegin();
    int std_val1 = *std_rit;
    ++std_rit;
    int std_val2 = *std_rit;
    --std_rit;
    int std_val3 = *std_rit;
    std_rit++;
    int std_val4 = *std_rit;
    std_rit--;
    int std_val5 = *std_rit;
    double std_time = std_timer.elapsed();
    
    passed = (ft_val1 == std_val1) && (ft_val2 == std_val2) && 
             (ft_val3 == std_val3) && (ft_val4 == std_val4) && 
             (ft_val5 == std_val5);
    
    if (!passed) {
        std::cout << "       Iterator operation mismatch\n";
        std::cout << "       ft:  " << ft_val1 << " " << ft_val2 << " " << ft_val3 
                  << " " << ft_val4 << " " << ft_val5 << "\n";
        std::cout << "       std: " << std_val1 << " " << std_val2 << " " << std_val3 
                  << " " << std_val4 << " " << std_val5 << "\n";
    }
    
    printResult("Reverse Iterator (++/-- operations)", passed, ft_time, std_time);
}

// Test 11: Reverse Iterator - modification through iterator
void testReverseIteratorModification() {
    const int N = 10000;
    ft::list<int> ft_l;
    std::list<int> std_l;
    bool passed = true;
    
    for (int i = 0; i < N; ++i) {
        ft_l.push_back(i);
        std_l.push_back(i);
    }
    
    Timer ft_timer;
    for (ft::list<int>::reverse_iterator rit = ft_l.rbegin(); rit != ft_l.rend(); ++rit) {
        *rit *= 2;
    }
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    for (std::list<int>::reverse_iterator rit = std_l.rbegin(); rit != std_l.rend(); ++rit) {
        *rit *= 2;
    }
    double std_time = std_timer.elapsed();
    
    passed = compareLists(ft_l, std_l);
    
    printResult("Reverse Iterator (modification)", passed, ft_time, std_time);
}

// Test 12: Reverse Iterator - const reverse iterator
void testConstReverseIterator() {
    const int N = 50000;
    ft::list<int> ft_l;
    std::list<int> std_l;
    bool passed = true;
    
    for (int i = 0; i < N; ++i) {
        ft_l.push_back(i);
        std_l.push_back(i);
    }
    
    const ft::list<int>& ft_const_l = ft_l;
    const std::list<int>& std_const_l = std_l;
    
    Timer ft_timer;
    int ft_sum = 0;
    for (ft::list<int>::const_reverse_iterator crit = ft_const_l.rbegin(); 
         crit != ft_const_l.rend(); ++crit) {
        ft_sum += *crit;
    }
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    int std_sum = 0;
    for (std::list<int>::const_reverse_iterator crit = std_const_l.rbegin(); 
         crit != std_const_l.rend(); ++crit) {
        std_sum += *crit;
    }
    double std_time = std_timer.elapsed();
    
    passed = (ft_sum == std_sum);
    
    if (!passed) {
        std::cout << "       Sum mismatch: ft=" << ft_sum << " std=" << std_sum << "\n";
    }
    
    printResult("Const Reverse Iterator", passed, ft_time, std_time);
}

// Test 13: Reverse Iterator - base() function
void testReverseIteratorBase() {
    ft::list<int> ft_l;
    std::list<int> std_l;
    bool passed = true;
    
    for (int i = 0; i < 10; ++i) {
        ft_l.push_back(i);
        std_l.push_back(i);
    }
    
    Timer ft_timer;
    ft::list<int>::reverse_iterator ft_rit = ft_l.rbegin();
    ++ft_rit; ++ft_rit; // Move two positions
    ft::list<int>::iterator ft_base_it = ft_rit.base();
    int ft_val = *ft_base_it;
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    std::list<int>::reverse_iterator std_rit = std_l.rbegin();
    ++std_rit; ++std_rit; // Move two positions
    std::list<int>::iterator std_base_it = std_rit.base();
    int std_val = *std_base_it;
    double std_time = std_timer.elapsed();
    
    passed = (ft_val == std_val);
    
    if (!passed) {
        std::cout << "       base() value mismatch: ft=" << ft_val 
                  << " std=" << std_val << "\n";
    }
    
    printResult("Reverse Iterator (base() function)", passed, ft_time, std_time);
}

// Test 14: Const Iterator - basic traversal
void testConstIteratorTraversal() {
    const int N = 50000;
    ft::list<int> ft_l;
    std::list<int> std_l;
    bool passed = true;
    
    for (int i = 0; i < N; ++i) {
        ft_l.push_back(i);
        std_l.push_back(i);
    }
    
    const ft::list<int>& ft_const_l = ft_l;
    const std::list<int>& std_const_l = std_l;
    
    Timer ft_timer;
    std::vector<int> ft_values;
    for (ft::list<int>::const_iterator cit = ft_const_l.begin(); 
         cit != ft_const_l.end(); ++cit) {
        ft_values.push_back(*cit);
    }
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    std::vector<int> std_values;
    for (std::list<int>::const_iterator cit = std_const_l.begin(); 
         cit != std_const_l.end(); ++cit) {
        std_values.push_back(*cit);
    }
    double std_time = std_timer.elapsed();
    
    if (ft_values.size() != std_values.size()) {
        passed = false;
        std::cout << "       Size mismatch\n";
    } else {
        for (size_t i = 0; i < ft_values.size(); ++i) {
            if (ft_values[i] != std_values[i]) {
                passed = false;
                std::cout << "       Value mismatch at pos " << i << "\n";
                break;
            }
        }
    }
    
    printResult("Const Iterator (traversal)", passed, ft_time, std_time);
}

// Test 15: Const Iterator - operations (++/--)
void testConstIteratorOperations() {
    ft::list<int> ft_l;
    std::list<int> std_l;
    bool passed = true;
    
    for (int i = 0; i < 100; ++i) {
        ft_l.push_back(i);
        std_l.push_back(i);
    }
    
    const ft::list<int>& ft_const_l = ft_l;
    const std::list<int>& std_const_l = std_l;
    
    Timer ft_timer;
    ft::list<int>::const_iterator ft_cit = ft_const_l.begin();
    int ft_val1 = *ft_cit;
    ++ft_cit;
    int ft_val2 = *ft_cit;
    ft_cit++;
    int ft_val3 = *ft_cit;
    --ft_cit;
    int ft_val4 = *ft_cit;
    ft_cit--;
    int ft_val5 = *ft_cit;
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    std::list<int>::const_iterator std_cit = std_const_l.begin();
    int std_val1 = *std_cit;
    ++std_cit;
    int std_val2 = *std_cit;
    std_cit++;
    int std_val3 = *std_cit;
    --std_cit;
    int std_val4 = *std_cit;
    std_cit--;
    int std_val5 = *std_cit;
    double std_time = std_timer.elapsed();
    
    passed = (ft_val1 == std_val1) && (ft_val2 == std_val2) && 
             (ft_val3 == std_val3) && (ft_val4 == std_val4) && 
             (ft_val5 == std_val5);
    
    if (!passed) {
        std::cout << "       Operation mismatch\n";
        std::cout << "       ft:  " << ft_val1 << " " << ft_val2 << " " << ft_val3 
                  << " " << ft_val4 << " " << ft_val5 << "\n";
        std::cout << "       std: " << std_val1 << " " << std_val2 << " " << std_val3 
                  << " " << std_val4 << " " << std_val5 << "\n";
    }
    
    printResult("Const Iterator (++/-- operations)", passed, ft_time, std_time);
}

// Test 16: Const Iterator - comparison operators
void testConstIteratorComparison() {
    ft::list<int> ft_l;
    std::list<int> std_l;
    bool passed = true;
    
    for (int i = 0; i < 10; ++i) {
        ft_l.push_back(i);
        std_l.push_back(i);
    }
    
    const ft::list<int>& ft_const_l = ft_l;
    const std::list<int>& std_const_l = std_l;
    
    Timer ft_timer;
    ft::list<int>::const_iterator ft_it1 = ft_const_l.begin();
    ft::list<int>::const_iterator ft_it2 = ft_const_l.begin();
    ft::list<int>::const_iterator ft_it3 = ft_const_l.begin();
    ++ft_it3;
    
    bool ft_eq = (ft_it1 == ft_it2);
    bool ft_neq = (ft_it1 != ft_it3);
    bool ft_eq_end = (ft_const_l.end() == ft_const_l.end());
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    std::list<int>::const_iterator std_it1 = std_const_l.begin();
    std::list<int>::const_iterator std_it2 = std_const_l.begin();
    std::list<int>::const_iterator std_it3 = std_const_l.begin();
    ++std_it3;
    
    bool std_eq = (std_it1 == std_it2);
    bool std_neq = (std_it1 != std_it3);
    bool std_eq_end = (std_const_l.end() == std_const_l.end());
    double std_time = std_timer.elapsed();
    
    passed = (ft_eq == std_eq) && (ft_neq == std_neq) && (ft_eq_end == std_eq_end);
    
    if (!passed) {
        std::cout << "       Comparison mismatch\n";
        std::cout << "       ft:  eq=" << ft_eq << " neq=" << ft_neq 
                  << " eq_end=" << ft_eq_end << "\n";
        std::cout << "       std: eq=" << std_eq << " neq=" << std_neq 
                  << " eq_end=" << std_eq_end << "\n";
    }
    
    printResult("Const Iterator (comparison operators)", passed, ft_time, std_time);
}

// Test 17: Const Iterator - mixed with regular iterators
void testConstIteratorMixedUsage() {
    ft::list<int> ft_l;
    std::list<int> std_l;
    bool passed = true;
    
    for (int i = 0; i < 1000; ++i) {
        ft_l.push_back(i);
        std_l.push_back(i);
    }
    
    Timer ft_timer;
    // Regular iterator to const iterator conversion
    ft::list<int>::iterator ft_it = ft_l.begin();
    ft::list<int>::const_iterator ft_cit = ft_it;
    
    // Compare regular and const iterators
    bool ft_comp1 = (ft_it == ft_cit);
    ++ft_it;
    bool ft_comp2 = (ft_it != ft_cit);
    
    // Use const iterator from non-const list
    int ft_sum = 0;
    for (ft::list<int>::const_iterator cit = ft_l.begin(); 
         cit != ft_l.end(); ++cit) {
        ft_sum += *cit;
    }
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    // Regular iterator to const iterator conversion
    std::list<int>::iterator std_it = std_l.begin();
    std::list<int>::const_iterator std_cit = std_it;
    
    // Compare regular and const iterators
    bool std_comp1 = (std_it == std_cit);
    ++std_it;
    bool std_comp2 = (std_it != std_cit);
    
    // Use const iterator from non-const list
    int std_sum = 0;
    for (std::list<int>::const_iterator cit = std_l.begin(); 
         cit != std_l.end(); ++cit) {
        std_sum += *cit;
    }
    double std_time = std_timer.elapsed();
    
    passed = (ft_comp1 == std_comp1) && (ft_comp2 == std_comp2) && 
             (ft_sum == std_sum);
    
    if (!passed) {
        std::cout << "       Mixed usage mismatch\n";
    }
    
    printResult("Const Iterator (mixed with regular iterators)", passed, ft_time, std_time);
}

// Test 18: Const Iterator - arrow operator
void testConstIteratorArrowOperator() {
    ft::list<std::pair<int, int> > ft_l;
    std::list<std::pair<int, int> > std_l;
    bool passed = true;
    
    for (int i = 0; i < 1000; ++i) {
        ft_l.push_back(std::make_pair(i, i * 2));
        std_l.push_back(std::make_pair(i, i * 2));
    }
    
    const ft::list<std::pair<int, int> >& ft_const_l = ft_l;
    const std::list<std::pair<int, int> >& std_const_l = std_l;
    
    Timer ft_timer;
    int ft_sum = 0;
    for (ft::list<std::pair<int, int> >::const_iterator cit = ft_const_l.begin(); 
         cit != ft_const_l.end(); ++cit) {
        ft_sum += cit->first + cit->second;
    }
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    int std_sum = 0;
    for (std::list<std::pair<int, int> >::const_iterator cit = std_const_l.begin(); 
         cit != std_const_l.end(); ++cit) {
        std_sum += cit->first + cit->second;
    }
    double std_time = std_timer.elapsed();
    
    passed = (ft_sum == std_sum);
    
    if (!passed) {
        std::cout << "       Arrow operator sum mismatch: ft=" << ft_sum 
                  << " std=" << std_sum << "\n";
    }
    
    printResult("Const Iterator (arrow operator)", passed, ft_time, std_time);
}

// Test 19: Const Iterator - with const methods
void testConstIteratorWithConstMethods() {
    ft::list<int> ft_l;
    std::list<int> std_l;
    bool passed = true;
    
    for (int i = 0; i < 5000; ++i) {
        ft_l.push_back(i);
        std_l.push_back(i);
    }
    
    const ft::list<int>& ft_const_l = ft_l;
    const std::list<int>& std_const_l = std_l;
    
    Timer ft_timer;
    size_t ft_size = ft_const_l.size();
    bool ft_empty = ft_const_l.empty();
    int ft_front = ft_const_l.front();
    int ft_back = ft_const_l.back();
    
    // Count elements using const iterator
    size_t ft_count = 0;
    for (ft::list<int>::const_iterator cit = ft_const_l.begin(); 
         cit != ft_const_l.end(); ++cit) {
        ++ft_count;
    }
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    size_t std_size = std_const_l.size();
    bool std_empty = std_const_l.empty();
    int std_front = std_const_l.front();
    int std_back = std_const_l.back();
    
    // Count elements using const iterator
    size_t std_count = 0;
    for (std::list<int>::const_iterator cit = std_const_l.begin(); 
         cit != std_const_l.end(); ++cit) {
        ++std_count;
    }
    double std_time = std_timer.elapsed();
    
    passed = (ft_size == std_size) && (ft_empty == std_empty) && 
             (ft_front == std_front) && (ft_back == std_back) && 
             (ft_count == std_count);
    
    if (!passed) {
        std::cout << "       Const methods mismatch\n";
    }
    
    printResult("Const Iterator (with const methods)", passed, ft_time, std_time);
}

void printSummary() {
    std::cout << BLUE << "\n========================================\n";
    std::cout << "           TEST SUMMARY\n";
    std::cout << "========================================\n" << RESET;
    
    int passed = 0;
    int total = results.size();
    double total_ft_time = 0;
    double total_std_time = 0;
    
    for (size_t i = 0; i < results.size(); ++i) {
        if (results[i].passed) ++passed;
        total_ft_time += results[i].ft_time;
        total_std_time += results[i].std_time;
    }
    
    std::cout << "Tests passed: " << passed << "/" << total << "\n";
    std::cout << "Total ft::list time: " << std::fixed << std::setprecision(2) 
              << total_ft_time << "ms\n";
    std::cout << "Total std::list time: " << total_std_time << "ms\n";
    if (total_std_time > 0) {
        std::cout << "Overall ratio: " << (total_ft_time / total_std_time) << "x\n";
    }
    
    if (passed == total) {
        std::cout << GREEN << "\n✓ All tests passed!\n" << RESET;
    } else {
        std::cout << RED << "\n✗ Some tests failed!\n" << RESET;
    }
}

int main() {
    std::cout << YELLOW << "========================================\n";
    std::cout << "  ft::list vs std::list Test Suite\n";
    std::cout << "========================================\n\n" << RESET;
    
    testBasicInsertion();
    testInsertAtPosition();
    testSort();
    testSpliceEntireList();
    testSpliceSingleElement();
    testSpliceRange();
    testIterators();
    testSortCustomComparator();
    testReverseIteratorTraversal();
    testReverseIteratorOperations();
    testReverseIteratorModification();
    testConstReverseIterator();
    testReverseIteratorBase();
    testConstIteratorTraversal();
    testConstIteratorOperations();
    testConstIteratorComparison();
    testConstIteratorMixedUsage();
    testConstIteratorArrowOperator();
    testConstIteratorWithConstMethods();
    
    printSummary();
    
    return 0;
}