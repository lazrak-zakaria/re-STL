#include <iostream>
#include <deque>
#include "../../deque.hpp"
#include <cassert>
#include <chrono>
#include <random>
#include <iomanip>

// Assuming ft::deque is your custom implementation
// Replace with your actual namespace/header
// namespace ft {
//     template<typename T>
//     using deque = std::deque<T>; // Replace this with your ft::deque
// }

// Color codes for output
#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

class Timer {
    std::chrono::high_resolution_clock::time_point start;
public:
    Timer() : start(std::chrono::high_resolution_clock::now()) {}
    double elapsed() {
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::milli>(end - start).count();
    }
};

template<typename T>
bool compare_deques(const std::deque<T>& std_deq, const ft::deque<T>& ft_deq) {
    if (std_deq.size() != ft_deq.size()) return false;
    for (size_t i = 0; i < std_deq.size(); ++i) {
        if (std_deq[i] != ft_deq[i]) return false;
    }
    return true;
}

void test_push_back() {
    std::cout << BLUE << "\n=== Testing push_back ===" << RESET << std::endl;
    
    std::deque<int> std_deq;
    ft::deque<int> ft_deq;
    const int N = 100000;
    
    Timer t1;
    for (int i = 0; i < N; ++i) {
        std_deq.push_back(i);
    }
    double std_time = t1.elapsed();
    
    Timer t2;
    for (int i = 0; i < N; ++i) {
        ft_deq.push_back(i);
    }
    double ft_time = t2.elapsed();
    
    bool match = compare_deques(std_deq, ft_deq);
    
    std::cout << "Pushed " << N << " elements" << std::endl;
    std::cout << "std::deque: " << std_time << " ms" << std::endl;
    std::cout << "ft::deque:  " << ft_time << " ms" << std::endl;
    std::cout << "Result: " << (match ? GREEN "PASS" : RED "FAIL") << RESET << std::endl;
}

void test_push_front() {
    std::cout << BLUE << "\n=== Testing push_front ===" << RESET << std::endl;
    
    std::deque<int> std_deq;
    ft::deque<int> ft_deq;
    const int N = 100000;
    
    Timer t1;
    for (int i = 0; i < N; ++i) {
        std_deq.push_front(i);
    }
    double std_time = t1.elapsed();
    
    Timer t2;
    for (int i = 0; i < N; ++i) {
        ft_deq.push_front(i);
    }
    double ft_time = t2.elapsed();
    
    bool match = compare_deques(std_deq, ft_deq);
    
    std::cout << "Pushed " << N << " elements to front" << std::endl;
    std::cout << "std::deque: " << std_time << " ms" << std::endl;
    std::cout << "ft::deque:  " << ft_time << " ms" << std::endl;
    std::cout << "Result: " << (match ? GREEN "PASS" : RED "FAIL") << RESET << std::endl;
}

void test_pop_back() {
    std::cout << BLUE << "\n=== Testing pop_back ===" << RESET << std::endl;
    
    const int N = 100000;
    std::deque<int> std_deq;
    ft::deque<int> ft_deq;
    
    for (int i = 0; i < N; ++i) {
        std_deq.push_back(i);
        ft_deq.push_back(i);
    }
    
    Timer t1;
    for (int i = 0; i < N / 2; ++i) {
        std_deq.pop_back();
    }
    double std_time = t1.elapsed();
    
    Timer t2;
    for (int i = 0; i < N / 2; ++i) {
        ft_deq.pop_back();
    }
    double ft_time = t2.elapsed();
    
    bool match = compare_deques(std_deq, ft_deq);
    
    std::cout << "Popped " << N/2 << " elements from back" << std::endl;
    std::cout << "std::deque: " << std_time << " ms" << std::endl;
    std::cout << "ft::deque:  " << ft_time << " ms" << std::endl;
    std::cout << "Result: " << (match ? GREEN "PASS" : RED "FAIL") << RESET << std::endl;
}

void test_pop_front() {
    std::cout << BLUE << "\n=== Testing pop_front ===" << RESET << std::endl;
    
    const int N = 100000;
    std::deque<int> std_deq;
    ft::deque<int> ft_deq;
    
    for (int i = 0; i < N; ++i) {
        std_deq.push_back(i);
        ft_deq.push_back(i);
    }
    
    Timer t1;
    for (int i = 0; i < N / 2; ++i) {
        std_deq.pop_front();
    }
    double std_time = t1.elapsed();
    
    Timer t2;
    for (int i = 0; i < N / 2; ++i) {
        ft_deq.pop_front();
    }
    double ft_time = t2.elapsed();
    
    bool match = compare_deques(std_deq, ft_deq);
    
    std::cout << "Popped " << N/2 << " elements from front" << std::endl;
    std::cout << "std::deque: " << std_time << " ms" << std::endl;
    std::cout << "ft::deque:  " << ft_time << " ms" << std::endl;
    std::cout << "Result: " << (match ? GREEN "PASS" : RED "FAIL") << RESET << std::endl;
}

void test_insert() {
    std::cout << BLUE << "\n=== Testing insert(pos, val) ===" << RESET << std::endl;
    
    std::deque<int> std_deq;
    ft::deque<int> ft_deq;
    const int N = 10000;
    
    // Pre-fill
    for (int i = 0; i < 1000; ++i) {
        std_deq.push_back(i);
        ft_deq.push_back(i);
    }
    
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(0, 999);
    
    Timer t1;
    for (int i = 0; i < N; ++i) {
        size_t pos = dist(rng) % (std_deq.size() + 1);
        std_deq.insert(std_deq.begin() + pos, i);
    }
    double std_time = t1.elapsed();
    
    rng.seed(42); // Reset for same sequence
    Timer t2;
    for (int i = 0; i < N; ++i) {
        size_t pos = dist(rng) % (ft_deq.size() + 1);
        ft_deq.insert(ft_deq.begin() + pos, i);
    }
    double ft_time = t2.elapsed();
    
    bool match = compare_deques(std_deq, ft_deq);
    
    std::cout << "Performed " << N << " random inserts" << std::endl;
    std::cout << "std::deque: " << std_time << " ms" << std::endl;
    std::cout << "ft::deque:  " << ft_time << " ms" << std::endl;
    std::cout << "Result: " << (match ? GREEN "PASS" : RED "FAIL") << RESET << std::endl;
}

void test_erase() {
    std::cout << BLUE << "\n=== Testing erase ===" << RESET << std::endl;
    
    const int N = 50000;
    std::deque<int> std_deq;
    ft::deque<int> ft_deq;
    
    for (int i = 0; i < N; ++i) {
        std_deq.push_back(i);
        ft_deq.push_back(i);
    }
    
    std::mt19937 rng(42);
    
    Timer t1;
    for (int i = 0; i < N / 2; ++i) {
        if (!std_deq.empty()) {
            size_t pos = rng() % std_deq.size();
            std_deq.erase(std_deq.begin() + pos);
        }
    }
    double std_time = t1.elapsed();
    
    rng.seed(42);
    Timer t2;
    for (int i = 0; i < N / 2; ++i) {
        if (!ft_deq.empty()) {
            size_t pos = rng() % ft_deq.size();
            ft_deq.erase(ft_deq.begin() + pos);
        }
    }
    double ft_time = t2.elapsed();
    
    bool match = compare_deques(std_deq, ft_deq);
    
    std::cout << "Performed " << N/2 << " random erases" << std::endl;
    std::cout << "std::deque: " << std_time << " ms" << std::endl;
    std::cout << "ft::deque:  " << ft_time << " ms" << std::endl;
    std::cout << "Result: " << (match ? GREEN "PASS" : RED "FAIL") << RESET << std::endl;
}

void test_resize() {
    std::cout << BLUE << "\n=== Testing resize ===" << RESET << std::endl;
    
    std::deque<int> std_deq;
    ft::deque<int> ft_deq;
    
    // Test 1: Resize up
    Timer t1;
    std_deq.resize(50000, 42);
    double std_time1 = t1.elapsed();
    
    Timer t2;
    ft_deq.resize(50000, 42);
    double ft_time1 = t2.elapsed();
    
    bool match1 = compare_deques(std_deq, ft_deq);
    
    // Test 2: Resize down
    Timer t3;
    std_deq.resize(10000);
    double std_time2 = t3.elapsed();
    
    Timer t4;
    ft_deq.resize(10000);
    double ft_time2 = t4.elapsed();
    
    bool match2 = compare_deques(std_deq, ft_deq);
    
    std::cout << "Resize up to 50000:" << std::endl;
    std::cout << "std::deque: " << std_time1 << " ms" << std::endl;
    std::cout << "ft::deque:  " << ft_time1 << " ms" << std::endl;
    std::cout << "Result: " << (match1 ? GREEN "PASS" : RED "FAIL") << RESET << std::endl;
    
    std::cout << "\nResize down to 10000:" << std::endl;
    std::cout << "std::deque: " << std_time2 << " ms" << std::endl;
    std::cout << "ft::deque:  " << ft_time2 << " ms" << std::endl;
    std::cout << "Result: " << (match2 ? GREEN "PASS" : RED "FAIL") << RESET << std::endl;
}

void test_assignment() {
    std::cout << BLUE << "\n=== Testing operator= ===" << RESET << std::endl;
    
    const int N = 100000;
    std::deque<int> std_deq1, std_deq2;
    ft::deque<int> ft_deq1, ft_deq2;
    
    for (int i = 0; i < N; ++i) {
        std_deq1.push_back(i);
        ft_deq1.push_back(i);
    }
    
    Timer t1;
    std_deq2 = std_deq1;
    double std_time = t1.elapsed();
    
    Timer t2;
    ft_deq2 = ft_deq1;
    double ft_time = t2.elapsed();
    
    bool match = compare_deques(std_deq2, ft_deq2);
    
    std::cout << "Assigned deque with " << N << " elements" << std::endl;
    std::cout << "std::deque: " << std_time << " ms" << std::endl;
    std::cout << "ft::deque:  " << ft_time << " ms" << std::endl;
    std::cout << "Result: " << (match ? GREEN "PASS" : RED "FAIL") << RESET << std::endl;
}

void test_clear() {
    std::cout << BLUE << "\n=== Testing clear ===" << RESET << std::endl;
    
    const int N = 100000;
    std::deque<int> std_deq;
    ft::deque<int> ft_deq;
    
    for (int i = 0; i < N; ++i) {
        std_deq.push_back(i);
        ft_deq.push_back(i);
    }
    
    Timer t1;
    std_deq.clear();
    double std_time = t1.elapsed();
    
    Timer t2;
    ft_deq.clear();
    double ft_time = t2.elapsed();
    
    bool match = (std_deq.size() == ft_deq.size() && std_deq.empty() == ft_deq.empty());
    
    std::cout << "Cleared deque with " << N << " elements" << std::endl;
    std::cout << "std::deque: " << std_time << " ms" << std::endl;
    std::cout << "ft::deque:  " << ft_time << " ms" << std::endl;
    std::cout << "Result: " << (match ? GREEN "PASS" : RED "FAIL") << RESET << std::endl;
}

void stress_test_combined() {
    std::cout << BLUE << "\n=== Combined Stress Test ===" << RESET << std::endl;
    
    std::deque<int> std_deq;
    ft::deque<int> ft_deq;
    std::mt19937 rng(12345);
    
    const int OPERATIONS = 50000;
    int passed = 0, total = 0;
    
    for (int i = 0; i < OPERATIONS; ++i) {
        int op = rng() % 8;
        
        try {
            switch (op) {
                case 0: // push_back
                    std_deq.push_back(i);
                    ft_deq.push_back(i);
                    break;
                case 1: // push_front
                    std_deq.push_front(i);
                    ft_deq.push_front(i);
                    break;
                case 2: // pop_back
                    if (!std_deq.empty()) {
                        std_deq.pop_back();
                        ft_deq.pop_back();
                    }
                    break;
                case 3: // pop_front
                    if (!std_deq.empty()) {
                        std_deq.pop_front();
                        ft_deq.pop_front();
                    }
                    break;
                case 4: // insert
                    if (!std_deq.empty()) {
                        size_t pos = rng() % std_deq.size();
                        std_deq.insert(std_deq.begin() + pos, i);
                        ft_deq.insert(ft_deq.begin() + pos, i);
                    }
                    break;
                case 5: // erase
                    if (!std_deq.empty()) {
                        size_t pos = rng() % std_deq.size();
                        std_deq.erase(std_deq.begin() + pos);
                        ft_deq.erase(ft_deq.begin() + pos);
                    }
                    break;
                case 6: // resize
                    {
                        size_t new_size = rng() % 1000;
                        std_deq.resize(new_size, 999);
                        ft_deq.resize(new_size, 999);
                    }
                    break;
                case 7: // clear
                    std_deq.clear();
                    ft_deq.clear();
                    break;
            }
            
            total++;
            if (compare_deques(std_deq, ft_deq)) {
                passed++;
            } else {
                std::cout << RED << "Mismatch at operation " << i << RESET << std::endl;
                return;
            }
        } catch (...) {
            std::cout << RED << "Exception at operation " << i << RESET << std::endl;
            return;
        }
    }
    
    std::cout << "Performed " << OPERATIONS << " mixed operations" << std::endl;
    std::cout << "Final size: " << std_deq.size() << std::endl;
    std::cout << "Result: " << GREEN << passed << "/" << total << " operations matched" << RESET << std::endl;
}

int main() {
    std::cout << YELLOW << "╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║  ft::deque vs std::deque Stress Test  ║" << std::endl;
    std::cout << "╚════════════════════════════════════════╝" << RESET << std::endl;
    
    test_push_back();
    test_push_front();
    test_pop_back();
    test_pop_front();
    test_insert();
    test_erase();
    test_resize();
    test_assignment();
    test_clear();
    stress_test_combined();
    
    std::cout << YELLOW << "\n✓ All tests completed!" << RESET << std::endl;
    
    return 0;
}