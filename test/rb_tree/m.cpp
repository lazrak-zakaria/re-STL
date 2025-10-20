#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "./../../set.hpp" // Your ft::set header
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>


void print_set_sample(const ft::set<int>& s, const std::string& label, size_t sample_size = 10) {
    std::cout << label << " [size: " << s.size() << "]";
    if (s.empty()) {
        std::cout << " (empty)" << std::endl;
        return;
    }
    
    if (s.size() <= sample_size * 2) {
        std::cout << ": ";
        for (ft::set<int>::const_iterator it = s.begin(); it != s.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "\n  First " << sample_size << ": ";
        ft::set<int>::const_iterator it = s.begin();
        for (size_t i = 0; i < sample_size && it != s.end(); ++i, ++it) {
            std::cout << *it << " ";
        }
        
        std::cout << "\n  Last " << sample_size << ": ";
        it = s.end();
        std::vector<int> last_elements;
        for (size_t i = 0; i < sample_size && it != s.begin(); ++i) {
            --it;
            last_elements.push_back(*it);
        }
        for (int i = last_elements.size() - 1; i >= 0; --i) {
            std::cout << last_elements[i] << " ";
        }
        std::cout << std::endl;
    }
}

void test_range_insert_large() {
    std::cout << "\n=== TEST RANGE INSERT (LARGE SCALE) ===" << std::endl;
    
    // Test 1: Insert 1 million sequential elements
    std::cout << "\n[Test 1] Inserting 1,000,000 sequential elements..." << std::endl;
    std::vector<int> vec_seq;
    vec_seq.reserve(1000000);
    for (int i = 0; i < 1000000; ++i) {
        vec_seq.push_back(i);
    }
    
    ft::set<int> s1;
    clock_t start = clock();
    s1.insert(vec_seq.begin(), vec_seq.end());
    clock_t end = clock();
    
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    print_set_sample(s1, "After range insert", 5);
    std::cout << "Time: " << elapsed << " seconds" << std::endl;
    
    // Test 2: Insert 1 million random elements
    std::cout << "\n[Test 2] Inserting 1,000,000 random elements..." << std::endl;
    std::vector<int> vec_rand;
    vec_rand.reserve(1000000);
    srand(42);  // Fixed seed for reproducibility
    for (int i = 0; i < 1000000; ++i) {
        vec_rand.push_back(rand() % 5000000);
    }
    
    ft::set<int> s2;
    start = clock();
    s2.insert(vec_rand.begin(), vec_rand.end());
    end = clock();
    
    elapsed = double(end - start) / CLOCKS_PER_SEC;
    print_set_sample(s2, "After range insert (with duplicates)", 5);
    std::cout << "Time: " << elapsed << " seconds" << std::endl;
    std::cout << "Note: Size < 1M due to duplicate random values" << std::endl;
    
    // Test 3: Range insert in chunks
    std::cout << "\n[Test 3] Inserting 500,000 elements in multiple ranges..." << std::endl;
    ft::set<int> s3;
    
    start = clock();
    // Insert first 250k
    s3.insert(vec_seq.begin(), vec_seq.begin() + 250000);
    // Insert next 250k
    s3.insert(vec_seq.begin() + 250000, vec_seq.begin() + 500000);
    end = clock();
    
    elapsed = double(end - start) / CLOCKS_PER_SEC;
    print_set_sample(s3, "After chunked insert", 5);
    std::cout << "Time: " << elapsed << " seconds" << std::endl;
}

void test_range_erase_large() {
    std::cout << "\n=== TEST RANGE ERASE (LARGE SCALE) ===" << std::endl;
    
    // Test 1: Create set with 1M elements and erase middle 500k
    std::cout << "\n[Test 1] Erasing middle 500,000 elements from 1M set..." << std::endl;
    ft::set<int> s1;
    for (int i = 0; i < 1000000; ++i) {
        s1.insert(i);
    }
    print_set_sample(s1, "Before erase", 5);
    
    ft::set<int>::iterator it_start = s1.find(250000);
    ft::set<int>::iterator it_end = s1.find(750000);
    
    clock_t start = clock();
    s1.erase(it_start, it_end);
    clock_t end = clock();
    
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    print_set_sample(s1, "After erase [250k, 750k)", 5);
    std::cout << "Time: " << elapsed << " seconds" << std::endl;
    
    // Test 2: Erase from beginning
    std::cout << "\n[Test 2] Erasing first 300,000 elements..." << std::endl;
    ft::set<int> s2;
    for (int i = 0; i < 1000000; ++i) {
        s2.insert(i);
    }
    
    it_end = s2.find(300000);
    start = clock();
    s2.erase(s2.begin(), it_end);
    end = clock();
    
    elapsed = double(end - start) / CLOCKS_PER_SEC;
    print_set_sample(s2, "After erase [begin, 300k)", 5);
    std::cout << "Time: " << elapsed << " seconds" << std::endl;
    
    // Test 3: Erase to end
    std::cout << "\n[Test 3] Erasing last 700,000 elements..." << std::endl;
    ft::set<int> s3;
    for (int i = 0; i < 1000000; ++i) {
        s3.insert(i);
    }
    
    it_start = s3.find(300000);
    start = clock();
    s3.erase(it_start, s3.end());
    end = clock();
    
    elapsed = double(end - start) / CLOCKS_PER_SEC;
    print_set_sample(s3, "After erase [300k, end)", 5);
    std::cout << "Time: " << elapsed << " seconds" << std::endl;
    
    // Test 4: Erase entire large set
    std::cout << "\n[Test 4] Erasing all 500,000 elements..." << std::endl;
    ft::set<int> s4;
    for (int i = 0; i < 500000; ++i) {
        s4.insert(i);
    }
    
    start = clock();
    s4.erase(s4.begin(), s4.end());
    end = clock();
    
    elapsed = double(end - start) / CLOCKS_PER_SEC;
    print_set_sample(s4, "After erase all", 5);
    std::cout << "Time: " << elapsed << " seconds" << std::endl;
}

void test_equal_range_large() {
    std::cout << "\n=== TEST EQUAL_RANGE (LARGE SCALE) ===" << std::endl;
    
    std::cout << "\nBuilding set with 1,000,000 elements..." << std::endl;
    ft::set<int> s;
    for (int i = 0; i < 1000000; ++i) {
        s.insert(i * 2);  // Even numbers: 0, 2, 4, 6, ...
    }
    print_set_sample(s, "Set", 5);
    
    // Test various positions
    int test_values[] = {0, 500000, 999998, 1, 500001, 999999, -100, 2000000};
    const char* descriptions[] = {
        "first element",
        "middle element",
        "last element",
        "non-existing (near start)",
        "non-existing (middle)",
        "non-existing (near end)",
        "less than all",
        "greater than all"
    };
    
    for (size_t i = 0; i < 8; ++i) {
        int val = test_values[i];
        std::cout << "\nequal_range(" << val << ") - " << descriptions[i] << ":" << std::endl;
        
        clock_t start = clock();
        ft::pair<ft::set<int>::iterator, ft::set<int>::iterator> range = s.equal_range(val);
        clock_t end = clock();
        
        double elapsed = double(end - start) / CLOCKS_PER_SEC;
        
        if (range.first == s.end()) {
            std::cout << "  lower_bound: end()" << std::endl;
        } else {
            std::cout << "  lower_bound: " << *range.first << std::endl;
        }
        
        if (range.second == s.end()) {
            std::cout << "  upper_bound: end()" << std::endl;
        } else {
            std::cout << "  upper_bound: " << *range.second << std::endl;
        }
        
        std::cout << "  Time: " << elapsed << " seconds" << std::endl;
    }
    
    // Performance test: many equal_range calls
    std::cout << "\n[Performance] Running 10,000 equal_range operations..." << std::endl;
    srand(42);
    clock_t start = clock();
    for (int i = 0; i < 10000; ++i) {
        int val = rand() % 2000000;
        s.equal_range(val);
    }
    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Total time: " << elapsed << " seconds" << std::endl;
    std::cout << "Average per operation: " << (elapsed / 10000) * 1000000 << " microseconds" << std::endl;
}

void test_clear_large() {
    std::cout << "\n=== TEST CLEAR (LARGE SCALE) ===" << std::endl;
    
    // Test 1: Clear 1 million elements
    std::cout << "\n[Test 1] Clearing 1,000,000 elements..." << std::endl;
    ft::set<int> s1;
    std::cout << "Building set..." << std::endl;
    for (int i = 0; i < 1000000; ++i) {
        s1.insert(i);
    }
    print_set_sample(s1, "Before clear", 5);
    
    clock_t start = clock();
    s1.clear();
    clock_t end = clock();
    
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    print_set_sample(s1, "After clear", 5);
    std::cout << "Time: " << elapsed << " seconds" << std::endl;
    
    // Test 2: Operations after clear
    std::cout << "\n[Test 2] Re-inserting 100,000 elements after clear..." << std::endl;
    start = clock();
    for (int i = 0; i < 100000; ++i) {
        s1.insert(i * 10);
    }
    end = clock();
    
    elapsed = double(end - start) / CLOCKS_PER_SEC;
    print_set_sample(s1, "After re-insert", 5);
    std::cout << "Time: " << elapsed << " seconds" << std::endl;
    
    // Test 3: Multiple clear operations
    std::cout << "\n[Test 3] Multiple clear operations..." << std::endl;
    ft::set<int> s2;
    
    for (int round = 1; round <= 3; ++round) {
        std::cout << "  Round " << round << ": Insert 200k, then clear..." << std::endl;
        for (int i = 0; i < 200000; ++i) {
            s2.insert(i);
        }
        start = clock();
        s2.clear();
        end = clock();
        elapsed = double(end - start) / CLOCKS_PER_SEC;
        std::cout << "    Clear time: " << elapsed << " seconds" << std::endl;
    }
    
    // Test 4: Clear empty set
    std::cout << "\n[Test 4] Clearing already empty set..." << std::endl;
    start = clock();
    s2.clear();
    end = clock();
    elapsed = double(end - start) / CLOCKS_PER_SEC;
    print_set_sample(s2, "After clearing empty set", 5);
    std::cout << "Time: " << elapsed << " seconds" << std::endl;
}

int main() {
    std::cout << "TESTING FT::SET RANGE OPERATIONS (LARGE SCALE)\n";
    std::cout << "================================================\n";
    std::cout << "Testing with up to 1,000,000 elements...\n";
    
    try {
        test_range_insert_large();
        test_range_erase_large();
        test_equal_range_large();
        test_clear_large();
        
        std::cout << "\n================================================\n";
        std::cout << "ALL TESTS COMPLETED SUCCESSFULLY!\n";
        
    } catch (const std::exception& e) {
        std::cerr << "\nEXCEPTION: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}