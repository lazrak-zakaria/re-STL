#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iomanip>
#include "../../vector.hpp"

// =============================
// Performance Timer
// =============================
class Timer {
    clock_t start_time;
public:
    Timer() : start_time(clock()) {}
    double elapsed() const {
        return double(clock() - start_time) / CLOCKS_PER_SEC;
    }
};

// =============================
// Helper Structures
// =============================
struct Heavy {
    int data[100];
    std::string str;
    
    Heavy(int val = 0) {
        std::stringstream ss;
        ss << val;
        str = ss.str();
        for (int i = 0; i < 100; ++i) data[i] = val + i;
    }
    
    Heavy(const Heavy& other) : str(other.str) {
        for (int i = 0; i < 100; ++i) data[i] = other.data[i];
    }
    
    Heavy& operator=(const Heavy& other) {
        if (this != &other) {
            str = other.str;
            for (int i = 0; i < 100; ++i) data[i] = other.data[i];
        }
        return *this;
    }
    
    bool operator==(const Heavy& other) const {
        if (str != other.str) return false;
        for (int i = 0; i < 100; ++i)
            if (data[i] != other.data[i]) return false;
        return true;
    }
};

// =============================
// Comparison Functions
// =============================
template<typename T>
bool compare(const ft::vector<T>& ft_v, const std::vector<T>& std_v) {
    if (ft_v.size() != std_v.size()) return false;
    if (ft_v.empty() != std_v.empty()) return false;
    for (size_t i = 0; i < ft_v.size(); ++i)
        if (ft_v[i] != std_v[i]) return false;
    return true;
}

// =============================
// Test Result Tracking
// =============================
struct TestResult {
    std::string name;
    bool passed;
    double ft_time;
    double std_time;
    double ratio;
    
    TestResult(const std::string& n, bool p, double ft, double st, double r)
        : name(n), passed(p), ft_time(ft), std_time(st), ratio(r) {}
};

std::vector<TestResult> results;

void print_result(const std::string& name, bool passed, double ft_time, double std_time) {
    double ratio = (std_time > 0) ? (ft_time / std_time) : 0;
    results.push_back(TestResult(name, passed, ft_time, std_time, ratio));
    
    std::cout << std::setw(50) << std::left << name << " | "
              << (passed ? "PASS" : "FAIL") << " | "
              << std::fixed << std::setprecision(4)
              << "ft: " << std::setw(8) << ft_time << "s | "
              << "std: " << std::setw(8) << std_time << "s | "
              << "ratio: " << std::setw(6) << ratio << "x\n";
}

// =============================
// Stress Tests
// =============================

// Test 1: Massive push_back
void test_massive_push_back() {
    const int N = 5000000;
    ft::vector<int> ft_v;
    std::vector<int> std_v;
    
    Timer ft_timer;
    for (int i = 0; i < N; ++i) ft_v.push_back(i);
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    for (int i = 0; i < N; ++i) std_v.push_back(i);
    double std_time = std_timer.elapsed();
    
    bool passed = (ft_v.size() == std_v.size() && ft_v[N-1] == std_v[N-1]);
    print_result("Massive push_back (5M elements)", passed, ft_time, std_time);
}

// Test 2: Large reserve and fill
void test_reserve_fill() {
    const int N = 10000000;
    ft::vector<int> ft_v;
    std::vector<int> std_v;
    
    Timer ft_timer;
    ft_v.reserve(N);
    for (int i = 0; i < N; ++i) ft_v.push_back(i % 1000);
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    std_v.reserve(N);
    for (int i = 0; i < N; ++i) std_v.push_back(i % 1000);
    double std_time = std_timer.elapsed();
    
    bool passed = compare(ft_v, std_v);
    print_result("Reserve + fill (10M elements)", passed, ft_time, std_time);
}

// Test 3: Repeated insert at front (worst case)
void test_insert_front() {
    const int N = 10000;
    ft::vector<int> ft_v;
    std::vector<int> std_v;
    
    Timer ft_timer;
    for (int i = 0; i < N; ++i) ft_v.insert(ft_v.begin(), i);
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    for (int i = 0; i < N; ++i) std_v.insert(std_v.begin(), i);
    double std_time = std_timer.elapsed();
    
    bool passed = compare(ft_v, std_v);
    print_result("Insert at front repeatedly (1K)", passed, ft_time, std_time);
}

// Test 4: Random access pattern
void test_random_access() {
    const int N = 1000000;
    const int ITERS = 10000000;
    
    ft::vector<int> ft_v(N);
    std::vector<int> std_v(N);
    for (int i = 0; i < N; ++i) {
        ft_v[i] = i;
        std_v[i] = i;
    }
    
    srand(42);
    Timer ft_timer;
    long long ft_sum = 0;
    for (int i = 0; i < ITERS; ++i) {
        ft_sum += ft_v[rand() % N];
    }
    double ft_time = ft_timer.elapsed();
    
    srand(42);
    Timer std_timer;
    long long std_sum = 0;
    for (int i = 0; i < ITERS; ++i) {
        std_sum += std_v[rand() % N];
    }
    double std_time = std_timer.elapsed();
    
    bool passed = (ft_sum == std_sum);
    print_result("Random access (10M accesses)", passed, ft_time, std_time);
}

// Test 5: Pop back stress
void test_pop_back() {
    const int N = 5000000;
    ft::vector<int> ft_v(N, 42);
    std::vector<int> std_v(N, 42);
    
    Timer ft_timer;
    while (!ft_v.empty()) ft_v.pop_back();
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    while (!std_v.empty()) std_v.pop_back();
    double std_time = std_timer.elapsed();
    
    bool passed = (ft_v.empty() && std_v.empty() && ft_v.size() == std_v.size());
    print_result("Pop back all (5M elements)", passed, ft_time, std_time);
}

// Test 6: Copy construction stress
void test_copy_construction() {
    const int N = 2000000;
    ft::vector<int> ft_src(N);
    std::vector<int> std_src(N);
    for (int i = 0; i < N; ++i) {
        ft_src[i] = i;
        std_src[i] = i;
    }
    
    Timer ft_timer;
    ft::vector<int> ft_v(ft_src);
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    std::vector<int> std_v(std_src);
    double std_time = std_timer.elapsed();
    
    bool passed = compare(ft_v, std_v);
    print_result("Copy construction (2M elements)", passed, ft_time, std_time);
}

// Test 7: Assignment operator stress
void test_assignment() {
    const int N = 2000000;
    ft::vector<int> ft_src(N, 99);
    std::vector<int> std_src(N, 99);
    ft::vector<int> ft_v;
    std::vector<int> std_v;
    
    Timer ft_timer;
    ft_v = ft_src;
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    std_v = std_src;
    double std_time = std_timer.elapsed();
    
    bool passed = compare(ft_v, std_v);
    print_result("Assignment operator (2M elements)", passed, ft_time, std_time);
}

// Test 8: Erase middle repeatedly
void test_erase_middle() {
    const int N = 20000;
    ft::vector<int> ft_v;
    std::vector<int> std_v;
    for (int i = 0; i < N; ++i) {
        ft_v.push_back(i);
        std_v.push_back(i);
    }
    
    Timer ft_timer;
    for (int i = 0; i < N/2; ++i) {
        if (!ft_v.empty()) ft_v.erase(ft_v.begin() + ft_v.size()/2);
    }
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    for (int i = 0; i < N/2; ++i) {
        if (!std_v.empty()) std_v.erase(std_v.begin() + std_v.size()/2);
    }
    double std_time = std_timer.elapsed();
    
    bool passed = compare(ft_v, std_v);
    print_result("Erase middle repeatedly (10K erases)", passed, ft_time, std_time);
}

// Test 9: Resize stress
void test_resize_stress() {
    const int N = 1000000;
    ft::vector<int> ft_v;
    std::vector<int> std_v;
    
    Timer ft_timer;
    for (int i = 0; i < 100; ++i) {
        ft_v.resize(N, i);
        ft_v.resize(N/2);
    }
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    for (int i = 0; i < 100; ++i) {
        std_v.resize(N, i);
        std_v.resize(N/2);
    }
    double std_time = std_timer.elapsed();
    
    bool passed = compare(ft_v, std_v);
    print_result("Resize oscillation (100 cycles)", passed, ft_time, std_time);
}

// Test 10: Clear and refill
void test_clear_refill() {
    const int N = 1000000;
    const int CYCLES = 50;
    ft::vector<int> ft_v;
    std::vector<int> std_v;
    
    Timer ft_timer;
    for (int c = 0; c < CYCLES; ++c) {
        for (int i = 0; i < N; ++i) ft_v.push_back(i);
        ft_v.clear();
    }
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    for (int c = 0; c < CYCLES; ++c) {
        for (int i = 0; i < N; ++i) std_v.push_back(i);
        std_v.clear();
    }
    double std_time = std_timer.elapsed();
    
    bool passed = compare(ft_v, std_v);
    print_result("Clear + refill cycles (50x1M)", passed, ft_time, std_time);
}

// Test 11: Heavy object handling
void test_heavy_objects() {
    const int N = 100000;
    ft::vector<Heavy> ft_v;
    std::vector<Heavy> std_v;
    
    Timer ft_timer;
    for (int i = 0; i < N; ++i) ft_v.push_back(Heavy(i));
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    for (int i = 0; i < N; ++i) std_v.push_back(Heavy(i));
    double std_time = std_timer.elapsed();
    
    bool passed = (ft_v.size() == std_v.size() && ft_v[0] == std_v[0]);
    print_result("Heavy objects (100K)", passed, ft_time, std_time);
}

// Test 12: Iterator intensive operations
void test_iterator_ops() {
    const int N = 1000000;
    const int ITERS = 1000;
    ft::vector<int> ft_v(N);
    std::vector<int> std_v(N);
    
    Timer ft_timer;
    for (int i = 0; i < ITERS; ++i) {
        for (ft::vector<int>::iterator it = ft_v.begin(); it != ft_v.end(); ++it) {
            *it = i;
        }
    }
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    for (int i = 0; i < ITERS; ++i) {
        for (std::vector<int>::iterator it = std_v.begin(); it != std_v.end(); ++it) {
            *it = i;
        }
    }
    double std_time = std_timer.elapsed();
    
    bool passed = compare(ft_v, std_v);
    print_result("Iterator traversal (1K x 1M)", passed, ft_time, std_time);
}

// Test 13: Swap stress
void test_swap() {
    const int N = 2000000;
    ft::vector<int> ft_v1(N, 1), ft_v2(N, 2);
    std::vector<int> std_v1(N, 1), std_v2(N, 2);
    
    Timer ft_timer;
    for (int i = 0; i < 1000; ++i) {
        ft_v1.swap(ft_v2);
    }
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    for (int i = 0; i < 1000; ++i) {
        std_v1.swap(std_v2);
    }
    double std_time = std_timer.elapsed();
    
    bool passed = compare(ft_v1, std_v1) && compare(ft_v2, std_v2);
    print_result("Swap iterations (1K x 2M)", passed, ft_time, std_time);
}

// Test 14: At() with exception handling
void test_at_exceptions() {
    const int N = 1000000;
    const int ATTEMPTS = 10000;
    ft::vector<int> ft_v(N, 42);
    std::vector<int> std_v(N, 42);
    
    int ft_caught = 0, std_caught = 0;
    
    Timer ft_timer;
    for (int i = 0; i < ATTEMPTS; ++i) {
        try {
            ft_v.at(N + i);
        } catch (const std::out_of_range&) {
            ++ft_caught;
        }
    }
    double ft_time = ft_timer.elapsed();
    
    Timer std_timer;
    for (int i = 0; i < ATTEMPTS; ++i) {
        try {
            std_v.at(N + i);
        } catch (const std::out_of_range&) {
            ++std_caught;
        }
    }
    double std_time = std_timer.elapsed();
    
    bool passed = (ft_caught == std_caught && ft_caught == ATTEMPTS);
    print_result("at() exceptions (10K)", passed, ft_time, std_time);
}

// Test 15: Mixed operations chaos
void test_mixed_chaos() {
    const int CYCLES = 10000;
    ft::vector<int> ft_v;
    std::vector<int> std_v;
    
    srand(42);
    Timer ft_timer;
    for (int i = 0; i < CYCLES; ++i) {
        int op = rand() % 6;
        switch (op) {
            case 0: ft_v.push_back(i); break;
            case 1: if (!ft_v.empty()) ft_v.pop_back(); break;
            case 2: ft_v.resize(rand() % 1000); break;
            case 3: if (!ft_v.empty()) ft_v.insert(ft_v.begin() + rand() % ft_v.size(), i); break;
            case 4: if (!ft_v.empty()) ft_v.erase(ft_v.begin() + rand() % ft_v.size()); break;
            case 5: ft_v.clear(); break;
        }
    }
    double ft_time = ft_timer.elapsed();
    
    srand(42);
    Timer std_timer;
    for (int i = 0; i < CYCLES; ++i) {
        int op = rand() % 6;
        switch (op) {
            case 0: std_v.push_back(i); break;
            case 1: if (!std_v.empty()) std_v.pop_back(); break;
            case 2: std_v.resize(rand() % 1000); break;
            case 3: if (!std_v.empty()) std_v.insert(std_v.begin() + rand() % std_v.size(), i); break;
            case 4: if (!std_v.empty()) std_v.erase(std_v.begin() + rand() % std_v.size()); break;
            case 5: std_v.clear(); break;
        }
    }
    double std_time = std_timer.elapsed();
    
    bool passed = compare(ft_v, std_v);
    print_result("Mixed chaos (10K operations)", passed, ft_time, std_time);
}

// =============================
// Main
// =============================
int main() {
    std::cout << "\n";
    std::cout << "================================================================================\n";
    std::cout << "          ft::vector COMPREHENSIVE STRESS TEST SUITE                        \n";
    std::cout << "================================================================================\n\n";
    
    test_massive_push_back();
    test_reserve_fill();
    test_insert_front();
    test_random_access();
    test_pop_back();
    test_copy_construction();
    test_assignment();
    test_erase_middle();
    test_resize_stress();
    test_clear_refill();
    test_heavy_objects();
    test_iterator_ops();
    test_swap();
    test_at_exceptions();
    test_mixed_chaos();
    
    // Summary
    std::cout << "\n";
    std::cout << "================================================================================\n";
    std::cout << "                            SUMMARY                                         \n";
    std::cout << "================================================================================\n";
    
    int passed = 0, failed = 0;
    double total_ft = 0, total_std = 0;
    
    for (size_t i = 0; i < results.size(); ++i) {
        const TestResult& r = results[i];
        if (r.passed) ++passed;
        else ++failed;
        total_ft += r.ft_time;
        total_std += r.std_time;
    }
    
    std::cout << "\nTests Passed: " << passed << "/" << results.size() << "\n";
    std::cout << "Tests Failed: " << failed << "/" << results.size() << "\n";
    std::cout << "Total ft::vector time:  " << std::fixed << std::setprecision(3) << total_ft << "s\n";
    std::cout << "Total std::vector time: " << total_std << "s\n";
    std::cout << "Average performance ratio: " << (total_std > 0 ? total_ft/total_std : 0) << "x\n";
    
    if (failed == 0) {
        std::cout << "\nALL TESTS PASSED!\n";
    } else {
        std::cout << "\nSOME TESTS FAILED\n";
    }
    
    std::cout << "\n";
    return (failed == 0) ? 0 : 1;
}