#include <iostream>
#include <deque>
#include <list>
#include <sstream>
#include <iterator>
#include <iomanip>
#include <ctime>
#include "../../deque.hpp"
#include <vector>

class Timer {
    clock_t start_time;
public:
    Timer() : start_time(clock()) {}
    void reset() { start_time = clock(); }
    double elapsed_ms() const {
        return (double(clock() - start_time) / CLOCKS_PER_SEC) * 1000.0;
    }
};

// Custom input iterator that only supports single-pass traversal
template<typename T>
class InputIterator {
    T* ptr;
    T* end_ptr;
public:
    typedef std::input_iterator_tag iterator_category;
    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
    
    InputIterator(T* p = NULL, T* e = NULL) : ptr(p), end_ptr(e) {}
    
    reference operator*() const { return *ptr; }
    pointer operator->() const { return ptr; }
    
    InputIterator& operator++() { ++ptr; return *this; }
    InputIterator operator++(int) { InputIterator tmp = *this; ++ptr; return tmp; }
    
    bool operator==(const InputIterator& other) const { return ptr == other.ptr; }
    bool operator!=(const InputIterator& other) const { return ptr != other.ptr; }
};

class InputIteratorTest {
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

    // Test 1: Insert with std::istream_iterator (true input iterator)
    static bool test_istream_iterator() {
        std::cout << "\n[1] Insert with istream_iterator (100K elements)... " << std::flush;
        Timer timer;
        
        // Create input string with 100K numbers
        std::stringstream ss_ft, ss_std;
        for (int i = 0; i < 100000; ++i) {
            ss_ft << i << " ";
            ss_std << i << " ";
        }
        
        ft::deque<int> ft_d;
        std::deque<int> std_d;
        
        timer.reset();
        std::istream_iterator<int> ft_begin(ss_ft), ft_end;
        ft_d.insert(ft_d.begin(), ft_begin, ft_end);
        double ft_time = timer.elapsed_ms();
        
        timer.reset();
        std::istream_iterator<int> std_begin(ss_std), std_end;
        std_d.insert(std_d.begin(), std_begin, std_end);
        double std_time = timer.elapsed_ms();
        
        bool pass = verify_equal(ft_d, std_d, "istream_iterator insert");
        std::cout << (pass ? "✓ PASS" : "✗ FAIL") 
                  << " | ft: " << ft_time << "ms, std: " << std_time 
                  << "ms, ratio: " << (ft_time/std_time) << "\n";
        return pass;
    }

    // Test 2: Insert with custom input iterator
    static bool test_custom_input_iterator() {
        std::cout << "[2] Insert with custom input iterator (100K)... " << std::flush;
        Timer timer;
        
        std::vector<int> source(100000);
        for (int i = 0; i < 100000; ++i) {
            source[i] = i * 2;
        }
        
        ft::deque<int> ft_d;
        std::deque<int> std_d;
        
        timer.reset();
        InputIterator<int> ft_begin(&source[0], &source[0] + source.size());
        InputIterator<int> ft_end(&source[0] + source.size(), &source[0] + source.size());
        ft_d.insert(ft_d.begin(), ft_begin, ft_end);
        double ft_time = timer.elapsed_ms();
        
        timer.reset();
        InputIterator<int> std_begin(&source[0], &source[0] + source.size());
        InputIterator<int> std_end(&source[0] + source.size(), &source[0] + source.size());
        std_d.insert(std_d.begin(), std_begin, std_end);
        double std_time = timer.elapsed_ms();
        
        bool pass = verify_equal(ft_d, std_d, "Custom input iterator insert");
        std::cout << (pass ? "✓ PASS" : "✗ FAIL") 
                  << " | ft: " << ft_time << "ms, std: " << std_time 
                  << "ms, ratio: " << (ft_time/std_time) << "\n";
        return pass;
    }

    // Test 3: Insert in middle with input iterator
    static bool test_insert_middle_input_iter() {
        std::cout << "[3] Insert in middle with input iterator (50K)... " << std::flush;
        Timer timer;
        
        ft::deque<int> ft_d;
        std::deque<int> std_d;
        
        // Pre-fill with 100K elements
        for (int i = 0; i < 100000; ++i) {
            ft_d.push_back(i);
            std_d.push_back(i);
        }
        
        std::vector<int> insert_data(50000);
        for (int i = 0; i < 50000; ++i) {
            insert_data[i] = 1000000 + i;
        }
        
        ft::deque<int>::iterator ft_pos = ft_d.begin();
        std::deque<int>::iterator std_pos = std_d.begin();
        std::advance(ft_pos, 50000);
        std::advance(std_pos, 50000);
        
        timer.reset();
        InputIterator<int> ft_begin(&insert_data[0], &insert_data[0] + insert_data.size());
        InputIterator<int> ft_end(&insert_data[0] + insert_data.size(), &insert_data[0] + insert_data.size());
        ft_d.insert(ft_pos, ft_begin, ft_end);
        double ft_time = timer.elapsed_ms();
        
        timer.reset();
        InputIterator<int> std_begin(&insert_data[0], &insert_data[0] + insert_data.size());
        InputIterator<int> std_end(&insert_data[0] + insert_data.size(), &insert_data[0] + insert_data.size());
        std_d.insert(std_pos, std_begin, std_end);
        double std_time = timer.elapsed_ms();
        
        bool pass = verify_equal(ft_d, std_d, "Insert middle input iter");
        std::cout << (pass ? "✓ PASS" : "✗ FAIL") 
                  << " | ft: " << ft_time << "ms, std: " << std_time 
                  << "ms, ratio: " << (ft_time/std_time) << "\n";
        return pass;
    }

    // Test 4: Assign with input iterator
    static bool test_assign_input_iter() {
        std::cout << "[4] Assign with input iterator (100K)... " << std::flush;
        Timer timer;
        
        ft::deque<int> ft_d;
        std::deque<int> std_d;
        
        // Pre-fill
        for (int i = 0; i < 50000; ++i) {
            ft_d.push_back(i);
            std_d.push_back(i);
        }
        
        std::vector<int> assign_data(100000);
        for (int i = 0; i < 100000; ++i) {
            assign_data[i] = i * 3;
        }
        
        timer.reset();
        InputIterator<int> ft_begin(&assign_data[0], &assign_data[0] + assign_data.size());
        InputIterator<int> ft_end(&assign_data[0] + assign_data.size(), &assign_data[0] + assign_data.size());
        ft_d.assign(ft_begin, ft_end);
        double ft_time = timer.elapsed_ms();
        
        timer.reset();
        InputIterator<int> std_begin(&assign_data[0], &assign_data[0] + assign_data.size());
        InputIterator<int> std_end(&assign_data[0] + assign_data.size(), &assign_data[0] + assign_data.size());
        std_d.assign(std_begin, std_end);
        double std_time = timer.elapsed_ms();
        
        bool pass = verify_equal(ft_d, std_d, "Assign input iter");
        std::cout << (pass ? "✓ PASS" : "✗ FAIL") 
                  << " | ft: " << ft_time << "ms, std: " << std_time 
                  << "ms, ratio: " << (ft_time/std_time) << "\n";
        return pass;
    }

    // Test 5: Range constructor with input iterator
    static bool test_range_constructor_input_iter() {
        std::cout << "[5] Range constructor with input iterator (100K)... " << std::flush;
        Timer timer;
        
        std::vector<int> source(100000);
        for (int i = 0; i < 100000; ++i) {
            source[i] = i + 42;
        }
        
        timer.reset();
        InputIterator<int> ft_begin(&source[0], &source[0] + source.size());
        InputIterator<int> ft_end(&source[0] + source.size(), &source[0] + source.size());
        ft::deque<int> ft_d(ft_begin, ft_end);
        double ft_time = timer.elapsed_ms();
        
        timer.reset();
        InputIterator<int> std_begin(&source[0], &source[0] + source.size());
        InputIterator<int> std_end(&source[0] + source.size(), &source[0] + source.size());
        std::deque<int> std_d(std_begin, std_end);
        double std_time = timer.elapsed_ms();
        
        bool pass = verify_equal(ft_d, std_d, "Range constructor input iter");
        std::cout << (pass ? "✓ PASS" : "✗ FAIL") 
                  << " | ft: " << ft_time << "ms, std: " << std_time 
                  << "ms, ratio: " << (ft_time/std_time) << "\n";
        return pass;
    }

    // Test 6: Insert at begin with input iterator
    static bool test_insert_begin_input_iter() {
        std::cout << "[6] Insert at begin with input iterator (100K)... " << std::flush;
        Timer timer;
        
        ft::deque<int> ft_d;
        std::deque<int> std_d;
        
        // Pre-fill with 100K
        for (int i = 0; i < 100000; ++i) {
            ft_d.push_back(i);
            std_d.push_back(i);
        }
        
        std::vector<int> insert_data(100000);
        for (int i = 0; i < 100000; ++i) {
            insert_data[i] = -i;
        }
        
        timer.reset();
        InputIterator<int> ft_begin(&insert_data[0], &insert_data[0] + insert_data.size());
        InputIterator<int> ft_end(&insert_data[0] + insert_data.size(), &insert_data[0] + insert_data.size());
        ft_d.insert(ft_d.begin(), ft_begin, ft_end);
        double ft_time = timer.elapsed_ms();
        
        timer.reset();
        InputIterator<int> std_begin(&insert_data[0], &insert_data[0] + insert_data.size());
        InputIterator<int> std_end(&insert_data[0] + insert_data.size(), &insert_data[0] + insert_data.size());
        std_d.insert(std_d.begin(), std_begin, std_end);
        double std_time = timer.elapsed_ms();
        
        bool pass = verify_equal(ft_d, std_d, "Insert begin input iter");
        std::cout << (pass ? "✓ PASS" : "✗ FAIL") 
                  << " | ft: " << ft_time << "ms, std: " << std_time 
                  << "ms, ratio: " << (ft_time/std_time) << "\n";
        return pass;
    }

    // Test 7: Insert at end with input iterator
    static bool test_insert_end_input_iter() {
        std::cout << "[7] Insert at end with input iterator (100K)... " << std::flush;
        Timer timer;
        
        ft::deque<int> ft_d;
        std::deque<int> std_d;
        
        // Pre-fill
        for (int i = 0; i < 100000; ++i) {
            ft_d.push_back(i);
            std_d.push_back(i);
        }
        
        std::vector<int> insert_data(100000);
        for (int i = 0; i < 100000; ++i) {
            insert_data[i] = 200000 + i;
        }
        
        timer.reset();
        InputIterator<int> ft_begin(&insert_data[0], &insert_data[0] + insert_data.size());
        InputIterator<int> ft_end(&insert_data[0] + insert_data.size(), &insert_data[0] + insert_data.size());
        ft_d.insert(ft_d.end(), ft_begin, ft_end);
        double ft_time = timer.elapsed_ms();
        
        timer.reset();
        InputIterator<int> std_begin(&insert_data[0], &insert_data[0] + insert_data.size());
        InputIterator<int> std_end(&insert_data[0] + insert_data.size(), &insert_data[0] + insert_data.size());
        std_d.insert(std_d.end(), std_begin, std_end);
        double std_time = timer.elapsed_ms();
        
        bool pass = verify_equal(ft_d, std_d, "Insert end input iter");
        std::cout << (pass ? "✓ PASS" : "✗ FAIL") 
                  << " | ft: " << ft_time << "ms, std: " << std_time 
                  << "ms, ratio: " << (ft_time/std_time) << "\n";
        return pass;
    }

    // Test 8: Multiple small inserts with input iterator
    static bool test_multiple_small_inserts() {
        std::cout << "[8] Multiple small inserts with input iter (1K x 100)... " << std::flush;
        Timer timer;
        
        ft::deque<int> ft_d;
        std::deque<int> std_d;
        
        std::vector<int> insert_data(1000);
        
        timer.reset();
        for (int batch = 0; batch < 100; ++batch) {
            for (int i = 0; i < 1000; ++i) {
                insert_data[i] = batch * 1000 + i;
            }
            
            ft::deque<int>::iterator pos = ft_d.begin();
            if (!ft_d.empty()) {
                std::advance(pos, ft_d.size() / 2);
            }
            
            InputIterator<int> begin(&insert_data[0], &insert_data[0] + insert_data.size());
            InputIterator<int> end(&insert_data[0] + insert_data.size(), &insert_data[0] + insert_data.size());
            ft_d.insert(pos, begin, end);
        }
        double ft_time = timer.elapsed_ms();
        
        timer.reset();
        for (int batch = 0; batch < 100; ++batch) {
            for (int i = 0; i < 1000; ++i) {
                insert_data[i] = batch * 1000 + i;
            }
            
            std::deque<int>::iterator pos = std_d.begin();
            if (!std_d.empty()) {
                std::advance(pos, std_d.size() / 2);
            }
            
            InputIterator<int> begin(&insert_data[0], &insert_data[0] + insert_data.size());
            InputIterator<int> end(&insert_data[0] + insert_data.size(), &insert_data[0] + insert_data.size());
            std_d.insert(pos, begin, end);
        }
        double std_time = timer.elapsed_ms();
        
        bool pass = verify_equal(ft_d, std_d, "Multiple small inserts");
        std::cout << (pass ? "✓ PASS" : "✗ FAIL") 
                  << " | ft: " << ft_time << "ms, std: " << std_time 
                  << "ms, ratio: " << (ft_time/std_time) << "\n";
        return pass;
    }

    // Test 9: Insert with list iterator (forward iterator, should NOT use input iter path)
    static bool test_list_iterator() {
        std::cout << "[9] Insert with list iterator (forward iter, 100K)... " << std::flush;
        Timer timer;
        
        std::list<int> source;
        for (int i = 0; i < 100000; ++i) {
            source.push_back(i);
        }
        
        ft::deque<int> ft_d;
        std::deque<int> std_d;
        
        timer.reset();
        ft_d.insert(ft_d.begin(), source.begin(), source.end());
        double ft_time = timer.elapsed_ms();
        
        timer.reset();
        std_d.insert(std_d.begin(), source.begin(), source.end());
        double std_time = timer.elapsed_ms();
        
        bool pass = verify_equal(ft_d, std_d, "List iterator insert");
        std::cout << (pass ? "✓ PASS" : "✗ FAIL") 
                  << " | ft: " << ft_time << "ms, std: " << std_time 
                  << "ms, ratio: " << (ft_time/std_time) 
                  << " (should use forward iter path)\n";
        return pass;
    }

    // Test 10: Empty input iterator
    static bool test_empty_input_iter() {
        std::cout << "[10] Insert with empty input iterator... " << std::flush;
        
        ft::deque<int> ft_d;
        std::deque<int> std_d;
        
        for (int i = 0; i < 100; ++i) {
            ft_d.push_back(i);
            std_d.push_back(i);
        }
        
        std::vector<int> empty_data;
        
        InputIterator<int> ft_begin(&empty_data[0], &empty_data[0]);
        InputIterator<int> ft_end(&empty_data[0], &empty_data[0]);
        ft_d.insert(ft_d.begin(), ft_begin, ft_end);
        
        InputIterator<int> std_begin(&empty_data[0], &empty_data[0]);
        InputIterator<int> std_end(&empty_data[0], &empty_data[0]);
        std_d.insert(std_d.begin(), std_begin, std_end);
        
        bool pass = verify_equal(ft_d, std_d, "Empty input iter");
        std::cout << (pass ? "✓ PASS" : "✗ FAIL") << "\n";
        return pass;
    }
};

int main() {
    std::cout << std::string(80, '=') << "\n";
    std::cout << "DEQUE INPUT ITERATOR TEST SUITE\n";
    std::cout << "Testing input iterator vs forward/random access iterator paths\n";
    std::cout << std::string(80, '=') << "\n";
    
    int passed = 0;
    int total = 10;
    
    if (InputIteratorTest::test_istream_iterator()) passed++;
    if (InputIteratorTest::test_custom_input_iterator()) passed++;
    if (InputIteratorTest::test_insert_middle_input_iter()) passed++;
    if (InputIteratorTest::test_assign_input_iter()) passed++;
    if (InputIteratorTest::test_range_constructor_input_iter()) passed++;
    if (InputIteratorTest::test_insert_begin_input_iter()) passed++;
    if (InputIteratorTest::test_insert_end_input_iter()) passed++;
    if (InputIteratorTest::test_multiple_small_inserts()) passed++;
    if (InputIteratorTest::test_list_iterator()) passed++;
    if (InputIteratorTest::test_empty_input_iter()) passed++;
    
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