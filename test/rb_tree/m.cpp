#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>

// Include your ft::set header
#include "../../set.hpp"

// Color codes
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define CYAN "\033[0;36m"
#define RESET "\033[0m"

// Stateful comparator - exactly like monkey tester
class stateful_comparator
{
private:
    int key;
public:
    stateful_comparator() : key(9) {}
    stateful_comparator(const stateful_comparator &other) : key(other.key) {}
    stateful_comparator &operator=(const stateful_comparator &other) {
        this->key = other.key;
        return *this;
    }
    bool operator()(const std::string &l, const std::string &r) const
    {
        return rotate(l) < rotate(r);
    }
    std::string rotate(std::string s) const
    {
        if (s.empty())
            return s;
        int shift = key % s.size();
        return s.substr(shift) + s.substr(0, shift);
    }
    friend bool operator==(const stateful_comparator &l, const stateful_comparator &r) {
        return l.key == r.key;
    }
    friend bool operator!=(const stateful_comparator &l, const stateful_comparator &r) {
        return l.key != r.key;
    }
    int get_key() const { return key; }
};

int test_num = 0;
int passed = 0;
int failed = 0;

void print_separator() {
    std::cout << std::string(70, '=') << "\n";
}

template<typename Set>
void print_set(const std::string& name, const Set& s) {
    std::cout << name << ": size=" << s.size() << ", content: [";
    typename Set::const_iterator it = s.begin();
    bool first = true;
    int count = 0;
    while (it != s.end() && count < 20) {  // Limit output
        if (!first) std::cout << ", ";
        std::cout << "\"" << *it << "\"";
        first = false;
        ++it;
        ++count;
    }
    if (it != s.end()) std::cout << ", ...";
    std::cout << "]\n";
}

template<typename FtSet, typename StdSet>
bool compare_sets(const FtSet& ft_s, const StdSet& std_s, bool verbose = true) {
    if (ft_s.size() != std_s.size()) {
        if (verbose) {
            std::cout << RED << "  ✗ Size mismatch: ft=" << ft_s.size() 
                      << " std=" << std_s.size() << RESET << "\n";
        }
        return false;
    }
    
    typename FtSet::const_iterator ft_it = ft_s.begin();
    typename StdSet::const_iterator std_it = std_s.begin();
    
    int pos = 0;
    while (ft_it != ft_s.end() && std_it != std_s.end()) {
        if (*ft_it != *std_it) {
            if (verbose) {
                std::cout << RED << "  ✗ Element mismatch at position " << pos 
                          << ": ft=\"" << *ft_it << "\" std=\"" << *std_it << "\"" << RESET << "\n";
            }
            return false;
        }
        ++ft_it;
        ++std_it;
        ++pos;
    }
    
    return ft_it == ft_s.end() && std_it == std_s.end();
}

void test_result(bool success, const std::string& msg) {
    test_num++;
    if (success) {
        std::cout << GREEN << "[TEST " << test_num << " PASS] " << msg << RESET << "\n";
        passed++;
    } else {
        std::cout << RED << "[TEST " << test_num << " FAIL] " << msg << RESET << "\n";
        failed++;
    }
}

// Test 1: Basic stateful comparator usage
void test_basic_stateful() {
    print_separator();
    std::cout << BLUE << "TEST: Basic Stateful Comparator" << RESET << "\n";
    
    ft::set<std::string, stateful_comparator> ft_s;
    std::set<std::string, stateful_comparator> std_s;
    
    std::vector<std::string> values;
    values.push_back("apple");
    values.push_back("banana");
    values.push_back("cherry");
    
    for (size_t i = 0; i < values.size(); i++) {
        ft_s.insert(values[i]);
        std_s.insert(values[i]);
    }
    
    std::cout << "Inserted: apple, banana, cherry\n";
    print_set("  ft_s ", ft_s);
    print_set("  std_s", std_s);
    
    test_result(compare_sets(ft_s, std_s), "Sets match with stateful comparator");
}

// Test 2: Check that comparators are different between instances
void test_different_comparators() {
    print_separator();
    std::cout << BLUE << "TEST: Different Comparators Have Different Keys" << RESET << "\n";
    
    ft::set<std::string, stateful_comparator> ft_a;
    ft::set<std::string, stateful_comparator> ft_b;
    
    stateful_comparator comp_a = ft_a.key_comp();
    stateful_comparator comp_b = ft_b.key_comp();
    
    std::cout << "Comparator A key: " << comp_a.get_key() << "\n";
    std::cout << "Comparator B key: " << comp_b.get_key() << "\n";
    
    bool different = (comp_a != comp_b);
    std::cout << "Comparators are different: " << (different ? "yes" : "no") << "\n";
    
    test_result(different, "Different set instances have different comparators");
}

// Test 3: Swap with stateful comparators - THE CRITICAL TEST
void test_swap_stateful_empty_filled() {
    print_separator();
    std::cout << BLUE << "TEST: Swap Empty/Filled with Stateful Comparator" << RESET << "\n";
    std::cout << CYAN << "This test reveals if you're swapping comparators!\n" << RESET;
    
    ft::set<std::string, stateful_comparator> ft_a, ft_b;
    std::set<std::string, stateful_comparator> std_a, std_b;
    
    // Get comparator keys before
    stateful_comparator ft_comp_a_before = ft_a.key_comp();
    stateful_comparator ft_comp_b_before = ft_b.key_comp();
    std::cout << "\nBefore swap:\n";
    std::cout << "  ft_a comparator key: " << ft_comp_a_before.get_key() << "\n";
    std::cout << "  ft_b comparator key: " << ft_comp_b_before.get_key() << "\n";
    
    // Fill b
    std::vector<std::string> values;
    values.push_back("apple");
    values.push_back("banana");
    values.push_back("cherry");
    
    for (size_t i = 0; i < values.size(); i++) {
        ft_b.insert(values[i]);
        std_b.insert(values[i]);
    }
    
    print_set("  ft_a ", ft_a);
    print_set("  ft_b ", ft_b);
    
    // Swap
    std::cout << "\nPerforming swap...\n";
    ft_a.swap(ft_b);
    std_a.swap(std_b);
    
    // Get comparator keys after
    stateful_comparator ft_comp_a_after = ft_a.key_comp();
    stateful_comparator ft_comp_b_after = ft_b.key_comp();
    std::cout << "\nAfter swap:\n";
    std::cout << "  ft_a comparator key: " << ft_comp_a_after.get_key() << "\n";
    std::cout << "  ft_b comparator key: " << ft_comp_b_after.get_key() << "\n";
    
    print_set("  ft_a ", ft_a);
    print_set("  std_a", std_a);
    print_set("  ft_b ", ft_b);
    print_set("  std_b", std_b);
    
    // CRITICAL CHECK: Comparators should NOT be swapped!
    // Each container should keep its original comparator
    bool comp_not_swapped = (ft_comp_a_after == ft_comp_a_before) && 
                            (ft_comp_b_after == ft_comp_b_before);
    
    if (!comp_not_swapped) {
        std::cout << RED << "\n  ✗ COMPARATORS WERE SWAPPED! This breaks the tree!\n" << RESET;
        std::cout << "  Original ft_a key: " << ft_comp_a_before.get_key() 
                  << " -> After: " << ft_comp_a_after.get_key() << "\n";
        std::cout << "  Original ft_b key: " << ft_comp_b_before.get_key() 
                  << " -> After: " << ft_comp_b_after.get_key() << "\n";
    } else {
        std::cout << GREEN << "\n  ✓ Comparators NOT swapped (correct!)\n" << RESET;
    }
    
    test_result(comp_not_swapped, "Comparators should NOT be swapped");
    
    bool a_match = compare_sets(ft_a, std_a);
    bool b_match = compare_sets(ft_b, std_b);
    
    test_result(a_match, "Container a matches after swap");
    test_result(b_match, "Container b matches after swap");
}

// Test 4: Swap two filled sets with stateful comparators
void test_swap_stateful_two_filled() {
    print_separator();
    std::cout << BLUE << "TEST: Swap Two Filled Sets with Stateful Comparator" << RESET << "\n";
    
    ft::set<std::string, stateful_comparator> ft_a, ft_b;
    std::set<std::string, stateful_comparator> std_a, std_b;
    
    // Get comparator keys
    stateful_comparator ft_comp_a_before = ft_a.key_comp();
    stateful_comparator ft_comp_b_before = ft_b.key_comp();
    std::cout << "Before:\n";
    std::cout << "  ft_a comparator key: " << ft_comp_a_before.get_key() << "\n";
    std::cout << "  ft_b comparator key: " << ft_comp_b_before.get_key() << "\n";
    
    // Fill both
    std::vector<std::string> values_a;
    values_a.push_back("dog");
    values_a.push_back("cat");
    
    for (size_t i = 0; i < values_a.size(); i++) {
        ft_a.insert(values_a[i]);
        std_a.insert(values_a[i]);
    }
    
    std::vector<std::string> values_b;
    values_b.push_back("x");
    values_b.push_back("y");
    values_b.push_back("z");
    
    for (size_t i = 0; i < values_b.size(); i++) {
        ft_b.insert(values_b[i]);
        std_b.insert(values_b[i]);
    }
    
    print_set("  ft_a ", ft_a);
    print_set("  ft_b ", ft_b);
    
    // Swap
    std::cout << "\nSwapping...\n";
    ft_a.swap(ft_b);
    std_a.swap(std_b);
    
    stateful_comparator ft_comp_a_after = ft_a.key_comp();
    stateful_comparator ft_comp_b_after = ft_b.key_comp();
    std::cout << "After:\n";
    std::cout << "  ft_a comparator key: " << ft_comp_a_after.get_key() << "\n";
    std::cout << "  ft_b comparator key: " << ft_comp_b_after.get_key() << "\n";
    
    print_set("  ft_a ", ft_a);
    print_set("  std_a", std_a);
    print_set("  ft_b ", ft_b);
    print_set("  std_b", std_b);
    
    bool comp_not_swapped = (ft_comp_a_after == ft_comp_a_before) && 
                            (ft_comp_b_after == ft_comp_b_before);
    
    test_result(comp_not_swapped, "Comparators should NOT be swapped");
    test_result(compare_sets(ft_a, std_a) && compare_sets(ft_b, std_b), 
                "Sets match after swap");
}

// Test 5: The exact monkey test scenario
void test_monkey_scenario() {
    print_separator();
    std::cout << BLUE << "TEST: Exact Monkey Test Scenario (Range Insert + Swap)" << RESET << "\n";
    
    ft::set<std::string, stateful_comparator> ft_a, ft_b;
    std::set<std::string, stateful_comparator> std_a, std_b;
    
    stateful_comparator ft_comp_a_before = ft_a.key_comp();
    stateful_comparator ft_comp_b_before = ft_b.key_comp();
    
    std::cout << "Initial comparator keys:\n";
    std::cout << "  ft_a: " << ft_comp_a_before.get_key() << "\n";
    std::cout << "  ft_b: " << ft_comp_b_before.get_key() << "\n\n";
    
    // Range from your failing test
    std::vector<std::string> range;
    range.push_back("ellnm");
    range.push_back("");
    range.push_back("amigo de la tornada");
    range.push_back("amigo de la tornada");  // duplicate
    range.push_back("hopkm");
    range.push_back("oqhnw");
    range.push_back("kuewh");
    range.push_back("qmgbb");
    range.push_back("qcljj");
    range.push_back("vswmd");
    range.push_back("qtbxi");
    range.push_back("mvtrr");
    range.push_back("ljptn");
    range.push_back("nfwzq");
    range.push_back("jmafa");
    range.push_back("rrwso");
    
    std::cout << "Inserting range into b...\n";
    ft_b.insert(range.begin(), range.end());
    std_b.insert(range.begin(), range.end());
    
    std::cout << "Before swap:\n";
    print_set("  ft_a ", ft_a);
    print_set("  ft_b ", ft_b);
    
    test_result(compare_sets(ft_b, std_b, false), "Container b correct after range insert");
    
    // Now swap (this is where it breaks)
    std::cout << "\nSwapping a and b...\n";
    ft_a.swap(ft_b);
    std_a.swap(std_b);
    
    stateful_comparator ft_comp_a_after = ft_a.key_comp();
    stateful_comparator ft_comp_b_after = ft_b.key_comp();
    
    std::cout << "\nAfter swap comparator keys:\n";
    std::cout << "  ft_a: " << ft_comp_a_after.get_key() << "\n";
    std::cout << "  ft_b: " << ft_comp_b_after.get_key() << "\n";
    
    if (ft_comp_a_after != ft_comp_a_before || ft_comp_b_after != ft_comp_b_before) {
        std::cout << RED << "\n  ✗ PROBLEM: Comparators were swapped!\n";
        std::cout << "  This means the tree in ft_a is ordered by key " 
                  << ft_comp_b_before.get_key() 
                  << " but being accessed with key " << ft_comp_a_after.get_key() << "\n";
        std::cout << "  Result: Iterator produces WRONG ORDER!\n" << RESET;
    }
    
    std::cout << "\nAfter swap:\n";
    print_set("  ft_a ", ft_a);
    print_set("  std_a", std_a);
    print_set("  ft_b ", ft_b);
    print_set("  std_b", std_b);
    
    bool comp_not_swapped = (ft_comp_a_after == ft_comp_a_before) && 
                            (ft_comp_b_after == ft_comp_b_before);
    bool a_match = compare_sets(ft_a, std_a);
    bool b_match = compare_sets(ft_b, std_b);
    
    test_result(comp_not_swapped, "Comparators NOT swapped");
    test_result(a_match, "Container a matches std::set");
    test_result(b_match, "Container b matches std::set");
}

// Test 6: Comparison operators with stateful comparator
void test_comparisons_stateful() {
    print_separator();
    std::cout << BLUE << "TEST: Comparison Operators with Stateful Comparator" << RESET << "\n";
    
    ft::set<std::string, stateful_comparator> ft_a, ft_b;
    std::set<std::string, stateful_comparator> std_a, std_b;
    
    ft_a.insert("test");
    std_a.insert("test");
    ft_b.insert("test");
    std_b.insert("test");
    
    bool ft_eq = (ft_a == ft_b);
    bool std_eq = (std_a == std_b);
    
    std::cout << "a == b: ft=" << ft_eq << ", std=" << std_eq << "\n";
    test_result(ft_eq == std_eq, "Equality with stateful comparator");
}

int main() {
    srand(time(NULL));
    
    std::cout << YELLOW << std::string(70, '=') << "\n";
    std::cout << "  FT::SET STATEFUL COMPARATOR TEST\n";
    std::cout << "  (Testing with monkey tester's stateful_comparator)\n";
    std::cout << std::string(70, '=') << RESET << "\n\n";
    
    test_basic_stateful();
    test_different_comparators();
    test_swap_stateful_empty_filled();
    test_swap_stateful_two_filled();
    test_monkey_scenario();
    test_comparisons_stateful();
    
    // Summary
    print_separator();
    std::cout << "\n";
    if (failed == 0) {
        std::cout << GREEN << "✓ ALL TESTS PASSED" << RESET;
    } else {
        std::cout << RED << "✗ SOME TESTS FAILED" << RESET;
    }
    std::cout << " (" << passed << "/" << (passed + failed) << ")\n";
    
    std::cout << "\n" << CYAN << "Key Insight:\n";
    std::cout << "If comparators are swapped, the tree structure becomes invalid!\n";
    std::cout << "The tree was built with comparator key X, but is now being\n";
    std::cout << "traversed with comparator key Y, producing wrong order.\n";
    std::cout << "\nFIX: Remove std::swap(cmp, other.cmp) from your swap() function!\n" 
              << RESET;
    
    print_separator();
    // ft::set<int> k;
    // k.insert(32);
    // *k.begin() = 34442;
    // std::cout << *k.begin() << "\n";
    return failed > 0 ? 1 : 0;
}