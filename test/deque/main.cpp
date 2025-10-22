#include <iostream>
#include <deque>
#include <vector>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "../../deque.hpp"

class Timer {
    clock_t start_time;
public:
    Timer() : start_time(clock()) {}
    void reset() { start_time = clock(); }
    double elapsed_ms() const {
        return (double(clock() - start_time) / CLOCKS_PER_SEC) * 1000.0;
    }
};

class StressTest {
public:
    template<typename Deque1, typename Deque2>
    static bool verify_equal(const Deque1& d1, const Deque2& d2, const std::string& test_name) {
        if (d1.size() != d2.size()) {
            std::cout << "✗ [" << test_name << "] SIZE MISMATCH: ft=" << d1.size() 
                      << ", std=" << d2.size() << "\n";
            return false;
        }
        
        typename Deque1::const_iterator it1 = d1.begin();
        typename Deque2::const_iterator it2 = d2.begin();
        
        for (size_t i = 0; i < d1.size(); ++i, ++it1, ++it2) {
            if (*it1 != *it2) {
                std::cout << "✗ [" << test_name << "] DATA MISMATCH at pos " << i 
                          << ": ft=" << *it1 << ", std=" << *it2 << "\n";
                return false;
            }
        }
        return true;
    }

    // Test 1: Sequential push_back with 1M elements
    static bool test_sequential_pushback_1m() {
        std::cout << "\n[1] Sequential push_back (1M elements)... " << std::flush;
        Timer timer;
        
        ft::deque<int> ft_d;
        std::deque<int> std_d;
        
        timer.reset();
        for (int i = 0; i < 1000000; ++i) {
            ft_d.push_back(i);
        }
        double ft_time = timer.elapsed_ms();
        
        timer.reset();
        for (int i = 0; i < 1000000; ++i) {
            std_d.push_back(i);
        }
        double std_time = timer.elapsed_ms();
        
        bool pass = verify_equal(ft_d, std_d, "Sequential push_back 1M");
        std::cout << (pass ? "✓ PASS" : "✗ FAIL") 
                  << " | ft: " << ft_time << "ms, std: " << std_time 
                  << "ms, ratio: " << (ft_time/std_time) << "\n";
        return pass;
    }

    // Test 2: Sequential push_front with 1M elements
    static bool test_sequential_pushfront_1m() {
        std::cout << "[2] Sequential push_front (1M elements)... " << std::flush;
        Timer timer;
        
        ft::deque<int> ft_d;
        std::deque<int> std_d;
        
        timer.reset();
        for (int i = 0; i < 1000000; ++i) {
            ft_d.push_front(i);
        }
        double ft_time = timer.elapsed_ms();
        
        timer.reset();
        for (int i = 0; i < 1000000; ++i) {
            std_d.push_front(i);
        }
        double std_time = timer.elapsed_ms();
        
        bool pass = verify_equal(ft_d, std_d, "Sequential push_front 1M");
        std::cout << (pass ? "✓ PASS" : "✗ FAIL") 
                  << " | ft: " << ft_time << "ms, std: " << std_time 
                  << "ms, ratio: " << (ft_time/std_time) << "\n";
        return pass;
    }

    // Test 3: Alternating push_back/push_front with 1M elements
    static bool test_alternating_push_1m() {
        std::cout << "[3] Alternating push_back/push_front (1M)... " << std::flush;
        Timer timer;
        
        ft::deque<int> ft_d;
        std::deque<int> std_d;
        
        timer.reset();
        for (int i = 0; i < 500000; ++i) {
            ft_d.push_back(i);
            ft_d.push_front(-i);
        }
        double ft_time = timer.elapsed_ms();
        
        timer.reset();
        for (int i = 0; i < 500000; ++i) {
            std_d.push_back(i);
            std_d.push_front(-i);
        }
        double std_time = timer.elapsed_ms();
        
        bool pass = verify_equal(ft_d, std_d, "Alternating push 1M");
        std::cout << (pass ? "✓ PASS" : "✗ FAIL") 
                  << " | ft: " << ft_time << "ms, std: " << std_time 
                  << "ms, ratio: " << (ft_time/std_time) << "\n";
        return pass;
    }

    // Test 4: Random access across 1M elements
    static bool test_random_access_1m() {
        std::cout << "[4] Random access (1M elements, 100K reads)... " << std::flush;
        
        ft::deque<int> ft_d;
        std::deque<int> std_d;
        
        for (int i = 0; i < 1000000; ++i) {
            ft_d.push_back(i * 2);
            std_d.push_back(i * 2);
        }
        
        Timer timer;
        long long ft_sum = 0;
        timer.reset();
        for (int i = 0; i < 100000; ++i) {
            size_t idx = (i * 7919) % 1000000;
            ft_sum += ft_d[idx];
        }
        double ft_time = timer.elapsed_ms();
        
        long long std_sum = 0;
        timer.reset();
        for (int i = 0; i < 100000; ++i) {
            size_t idx = (i * 7919) % 1000000;
            std_sum += std_d[idx];
        }
        double std_time = timer.elapsed_ms();
        
        bool pass = (ft_sum == std_sum) && verify_equal(ft_d, std_d, "Random access 1M");
        std::cout << (pass ? "✓ PASS" : "✗ FAIL") 
                  << " | ft: " << ft_time << "ms, std: " << std_time 
                  << "ms, ratio: " << (ft_time/std_time) << "\n";
        return pass;
    }

    // Test 5: Iterator traversal of 1M elements
    static bool test_iterator_traversal_1m() {
        std::cout << "[5] Iterator traversal (1M elements)... " << std::flush;
        
        ft::deque<int> ft_d;
        std::deque<int> std_d;
        
        for (int i = 0; i < 1000000; ++i) {
            ft_d.push_back(i);
            std_d.push_back(i);
        }
        
        Timer timer;
        long long ft_sum = 0;
        timer.reset();
        for (ft::deque<int>::iterator it = ft_d.begin(); it != ft_d.end(); ++it) {
            ft_sum += *it;
        }
        double ft_time = timer.elapsed_ms();
        
        long long std_sum = 0;
        timer.reset();
        for (std::deque<int>::iterator it = std_d.begin(); it != std_d.end(); ++it) {
            std_sum += *it;
        }
        double std_time = timer.elapsed_ms();
        
        bool pass = (ft_sum == std_sum);
        std::cout << (pass ? "✓ PASS" : "✗ FAIL") 
                  << " | ft: " << ft_time << "ms, std: " << std_time 
                  << "ms, ratio: " << (ft_time/std_time) << "\n";
        return pass;
    }

    // Test 6: Pop operations on 1M elements
    static bool test_pop_operations_1m() {
        std::cout << "[6] Pop operations (1M push + 1M pop)... " << std::flush;
        Timer timer;
        
        ft::deque<int> ft_d;
        std::deque<int> std_d;
        
        // Fill
        for (int i = 0; i < 1000000; ++i) {
            ft_d.push_back(i);
            std_d.push_back(i);
        }
        
        // Pop back
        timer.reset();
        for (int i = 0; i < 500000; ++i) {
            ft_d.pop_back();
        }
        double ft_popback_time = timer.elapsed_ms();
        
        timer.reset();
        for (int i = 0; i < 500000; ++i) {
            std_d.pop_back();
        }
        double std_popback_time = timer.elapsed_ms();
        
        // Pop front
        timer.reset();
        for (int i = 0; i < 500000; ++i) {
            ft_d.pop_front();
        }
        double ft_popfront_time = timer.elapsed_ms();
        
        timer.reset();
        for (int i = 0; i < 500000; ++i) {
            std_d.pop_front();
        }
        double std_popfront_time = timer.elapsed_ms();
        
        double ft_time = ft_popback_time + ft_popfront_time;
        double std_time = std_popback_time + std_popfront_time;
        
        bool pass = verify_equal(ft_d, std_d, "Pop operations 1M");
        std::cout << (pass ? "✓ PASS" : "✗ FAIL") 
                  << " | ft: " << ft_time << "ms, std: " << std_time 
                  << "ms, ratio: " << (ft_time/std_time) << "\n";
        return pass;
    }

    // Test 7: Insert in middle with large data
    static bool test_insert_middle_large() {
        std::cout << "[7] Insert in middle (500K + 100K insert)... " << std::flush;
        Timer timer;
        
        ft::deque<int> ft_d;
        std::deque<int> std_d;
        
        for (int i = 0; i < 500000; ++i) {
            ft_d.push_back(i);
            std_d.push_back(i);
        }
        
        std::vector<int> insert_data(100000);
        for (int i = 0; i < 100000; ++i) {
            insert_data[i] = 1000000 + i;
        }
        
        ft::deque<int>::iterator ft_it = ft_d.begin();
        std::deque<int>::iterator std_it = std_d.begin();
        std::advance(ft_it, 250000);
        std::advance(std_it, 250000);
        
        timer.reset();
        ft_d.insert(ft_it, insert_data.begin(), insert_data.end());
        double ft_time = timer.elapsed_ms();
        
        timer.reset();
        std_d.insert(std_it, insert_data.begin(), insert_data.end());
        double std_time = timer.elapsed_ms();
        
        bool pass = verify_equal(ft_d, std_d, "Insert middle large");
        std::cout << (pass ? "✓ PASS" : "✗ FAIL") 
                  << " | ft: " << ft_time << "ms, std: " << std_time 
                  << "ms, ratio: " << (ft_time/std_time) << "\n";
        return pass;
    }

    // Test 8: Erase in middle with large data
    static bool test_erase_middle_large() {
        std::cout << "[8] Erase in middle (1M - 200K erase)... " << std::flush;
        Timer timer;
        
        ft::deque<int> ft_d;
        std::deque<int> std_d;
        
        for (int i = 0; i < 1000000; ++i) {
            ft_d.push_back(i);
            std_d.push_back(i);
        }
        
        ft::deque<int>::iterator ft_start = ft_d.begin();
        ft::deque<int>::iterator ft_end = ft_d.begin();
        std::deque<int>::iterator std_start = std_d.begin();
        std::deque<int>::iterator std_end = std_d.begin();
        
        std::advance(ft_start, 400000);
        std::advance(ft_end, 600000);
        std::advance(std_start, 400000);
        std::advance(std_end, 600000);
        
        timer.reset();
        ft_d.erase(ft_start, ft_end);
        double ft_time = timer.elapsed_ms();
        
        timer.reset();
        std_d.erase(std_start, std_end);
        double std_time = timer.elapsed_ms();
        
        bool pass = verify_equal(ft_d, std_d, "Erase middle large");
        std::cout << (pass ? "✓ PASS" : "✗ FAIL") 
                  << " | ft: " << ft_time << "ms, std: " << std_time 
                  << "ms, ratio: " << (ft_time/std_time) << "\n";
        return pass;
    }

    // Test 9: Copy and assignment with 1M elements
    static bool test_copy_assignment_1m() {
        std::cout << "[9] Copy & assignment (1M elements)... " << std::flush;
        Timer timer;
        
        ft::deque<int> ft_orig;
        std::deque<int> std_orig;
        
        for (int i = 0; i < 1000000; ++i) {
            ft_orig.push_back(i);
            std_orig.push_back(i);
        }
        
        // Copy constructor
        timer.reset();
        ft::deque<int> ft_copy(ft_orig);
        double ft_copy_time = timer.elapsed_ms();
        
        timer.reset();
        std::deque<int> std_copy(std_orig);
        double std_copy_time = timer.elapsed_ms();
        
        // Assignment operator
        ft::deque<int> ft_assign;
        std::deque<int> std_assign;
        
        timer.reset();
        ft_assign = ft_orig;
        double ft_assign_time = timer.elapsed_ms();
        
        timer.reset();
        std_assign = std_orig;
        double std_assign_time = timer.elapsed_ms();
        
        double ft_time = ft_copy_time + ft_assign_time;
        double std_time = std_copy_time + std_assign_time;
        
        bool pass = verify_equal(ft_copy, std_copy, "Copy 1M") && 
                    verify_equal(ft_assign, std_assign, "Assign 1M");
        std::cout << (pass ? "✓ PASS" : "✗ FAIL") 
                  << " | ft: " << ft_time << "ms, std: " << std_time 
                  << "ms, ratio: " << (ft_time/std_time) << "\n";
        return pass;
    }

    // Test 10: Clear and refill with 1M elements
    static bool test_clear_refill_1m() {
        std::cout << "[10] Clear & refill (1M elements x2)... " << std::flush;
        Timer timer;
        
        ft::deque<int> ft_d;
        std::deque<int> std_d;
        
        // First fill
        for (int i = 0; i < 1000000; ++i) {
            ft_d.push_back(i);
            std_d.push_back(i);
        }
        
        timer.reset();
        ft_d.clear();
        for (int i = 0; i < 1000000; ++i) {
            ft_d.push_back(i * 2);
        }
        double ft_time = timer.elapsed_ms();
        
        timer.reset();
        std_d.clear();
        for (int i = 0; i < 1000000; ++i) {
            std_d.push_back(i * 2);
        }
        double std_time = timer.elapsed_ms();
        
        bool pass = verify_equal(ft_d, std_d, "Clear & refill 1M");
        std::cout << (pass ? "✓ PASS" : "✗ FAIL") 
                  << " | ft: " << ft_time << "ms, std: " << std_time 
                  << "ms, ratio: " << (ft_time/std_time) << "\n";
        return pass;
    }

    // Test 11: Mixed operations stress test
    static bool test_mixed_operations() {
        std::cout << "[11] Mixed operations (push/pop/insert/erase)... " << std::flush;
        Timer timer;
        
        ft::deque<int> ft_d;
        std::deque<int> std_d;
        
        timer.reset();
        // Phase 1: Build up
        for (int i = 0; i < 250000; ++i) {
            ft_d.push_back(i);
            if (i % 2 == 0) ft_d.push_front(-i);
        }
        
        // Phase 2: Insert in middle
        ft::deque<int>::iterator ft_mid = ft_d.begin();
        std::advance(ft_mid, ft_d.size() / 2);
        for (int i = 0; i < 50000; ++i) {
            ft_d.insert(ft_mid, 999);
        }
        
        // Phase 3: Pop some
        for (int i = 0; i < 100000; ++i) {
            if (i % 2 == 0) ft_d.pop_back();
            else ft_d.pop_front();
        }
        double ft_time = timer.elapsed_ms();
        
        timer.reset();
        // Same for std
        for (int i = 0; i < 250000; ++i) {
            std_d.push_back(i);
            if (i % 2 == 0) std_d.push_front(-i);
        }
        
        std::deque<int>::iterator std_mid = std_d.begin();
        std::advance(std_mid, std_d.size() / 2);
        for (int i = 0; i < 50000; ++i) {
            std_d.insert(std_mid, 999);
        }
        
        for (int i = 0; i < 100000; ++i) {
            if (i % 2 == 0) std_d.pop_back();
            else std_d.pop_front();
        }
        double std_time = timer.elapsed_ms();
        
        bool pass = verify_equal(ft_d, std_d, "Mixed operations");
        std::cout << (pass ? "✓ PASS" : "✗ FAIL") 
                  << " | ft: " << ft_time << "ms, std: " << std_time 
                  << "ms, ratio: " << (ft_time/std_time) << "\n";
        return pass;
    }

    // Test 12: Resize operations
    static bool test_resize_operations() {
        std::cout << "[12] Resize operations (1M elements)... " << std::flush;
        Timer timer;
        
        ft::deque<int> ft_d;
        std::deque<int> std_d;
        
        timer.reset();
        ft_d.resize(1000000, 42);
        ft_d.resize(500000);
        ft_d.resize(750000, 99);
        double ft_time = timer.elapsed_ms();
        
        timer.reset();
        std_d.resize(1000000, 42);
        std_d.resize(500000);
        std_d.resize(750000, 99);
        double std_time = timer.elapsed_ms();
        
        bool pass = verify_equal(ft_d, std_d, "Resize operations");
        std::cout << (pass ? "✓ PASS" : "✗ FAIL") 
                  << " | ft: " << ft_time << "ms, std: " << std_time 
                  << "ms, ratio: " << (ft_time/std_time) << "\n";
        return pass;
    }
};

int main() {
    std::cout << std::string(80, '=') << "\n";
    std::cout << "DEQUE STRESS TEST SUITE - 1M VALUES\n";
    std::cout << "Verifying ft::deque matches std::deque behavior\n";
    std::cout << std::string(80, '=') << "\n";
    
    int passed = 0;
    int total = 12;
    
    if (StressTest::test_sequential_pushback_1m()) passed++;
    if (StressTest::test_sequential_pushfront_1m()) passed++;
    if (StressTest::test_alternating_push_1m()) passed++;
    if (StressTest::test_random_access_1m()) passed++;
    if (StressTest::test_iterator_traversal_1m()) passed++;
    if (StressTest::test_pop_operations_1m()) passed++;
    if (StressTest::test_insert_middle_large()) passed++;
    if (StressTest::test_erase_middle_large()) passed++;
    if (StressTest::test_copy_assignment_1m()) passed++;
    if (StressTest::test_clear_refill_1m()) passed++;
    if (StressTest::test_mixed_operations()) passed++;
    if (StressTest::test_resize_operations()) passed++;
    
    std::cout << "\n" << std::string(80, '=') << "\n";
    std::cout << "RESULTS: " << passed << "/" << total << " tests passed";
    if (passed == total) {
        std::cout << " ✓ ALL TESTS PASSED!\n";
    } else {
        std::cout << " ✗ " << (total - passed) << " tests failed\n";
    }
    std::cout << std::string(80, '=') << "\n";
    
    return (passed == total) ? 0 : 1;
}