#include <iostream>
#include <queue>
#include <deque>
#include <ctime>
#include "../../queue.hpp" // your ft::queue

// Utility: compare two queues element-by-element
template <typename T>
bool equal_queues(ft::queue<T> ft_q, std::queue<T> std_q) {
    if (ft_q.size() != std_q.size()) return false;
    while (!ft_q.empty()) {
        if (ft_q.front() != std_q.front()) return false;
        ft_q.pop();
        std_q.pop();
    }
    return true;
}

// Utility: print comparison operator results
template <typename Q1, typename Q2>
void print_compare(const Q1& a, const Q2& b, const std::string& nameA, const std::string& nameB) {
    std::cout << "Comparing " << nameA << " and " << nameB << ":\n";
    std::cout << "  == " << (a == b) << "\n";
    std::cout << "  != " << (a != b) << "\n";
    std::cout << "  <  " << (a < b)  << "\n";
    std::cout << "  <= " << (a <= b) << "\n";
    std::cout << "  >  " << (a > b)  << "\n";
    std::cout << "  >= " << (a >= b) << "\n\n";
}

int main() {
    const int N = 500000; // half a million elements for stress

    std::cout << "==== QUEUE FUNCTIONAL & PERFORMANCE TEST ====\n";
    std::cout << "Elements: " << N << "\n\n";

    // -----------------------------------------------------
    // 1. Insertion performance test
    // -----------------------------------------------------
    ft::queue<int> ft_q;
    std::queue<int> std_q;

    clock_t ft_insert_start = std::clock();
    for (int i = 0; i < N; ++i)
        ft_q.push(i);
    clock_t ft_insert_end = std::clock();

    clock_t std_insert_start = std::clock();
    for (int i = 0; i < N; ++i)
        std_q.push(i);
    clock_t std_insert_end = std::clock();

    std::cout << "Insertion time:\n";
    std::cout << "  ft  : " << double(ft_insert_end - ft_insert_start) / CLOCKS_PER_SEC << "s\n";
    std::cout << "  std : " << double(std_insert_end - std_insert_start) / CLOCKS_PER_SEC << "s\n\n";

    // -----------------------------------------------------
    // 2. Functional correctness check
    // -----------------------------------------------------
    bool ok = true;
    for (int i = 0; i < 10; ++i) { // check first few values
        if (ft_q.front() != std_q.front()) ok = false;
        ft_q.pop();
        std_q.pop();
    }

    if (!ok)
        std::cout << "❌ Front pop mismatch detected\n";
    else
        std::cout << "✅ Basic front/back operations correct\n\n";

    // -----------------------------------------------------
    // 3. Operator comparison test
    // -----------------------------------------------------
    ft::queue<int> ft_a;
    ft::queue<int> ft_b;

    std::queue<int> std_a;
    std::queue<int> std_b;

    for (int i = 0; i < 5; ++i) {
        ft_a.push(i);
        std_a.push(i);
    }

    for (int i = 0; i < 5; ++i) {
        ft_b.push(i);
        std_b.push(i);
    }

    // make ft_b slightly different
    ft_b.push(99);
    std_b.push(99);

    std::cout << "---- Operator comparisons ----\n";
    print_compare(ft_a, ft_b, "ft_a", "ft_b");
    print_compare(std_a, std_b, "std_a", "std_b");

    // -----------------------------------------------------
    // 4. Full equality validation
    // -----------------------------------------------------
    ft::queue<int> ft_c;
    std::queue<int> std_c;
    for (int i = 0; i < 100; ++i) {
        ft_c.push(i * 3);
        std_c.push(i * 3);
    }

    bool same = equal_queues(ft_c, std_c);
    std::cout << (same ? "✅ All elements identical to std::queue\n"
                       : "❌ Queue contents differ from std::queue\n");

    // -----------------------------------------------------
    // 5. Pop performance
    // -----------------------------------------------------
    ft::queue<int> ft_popq = ft_c;
    std::queue<int> std_popq = std_c;

    clock_t ft_pop_start = std::clock();
    while (!ft_popq.empty()) ft_popq.pop();
    clock_t ft_pop_end = std::clock();

    clock_t std_pop_start = std::clock();
    while (!std_popq.empty()) std_popq.pop();
    clock_t std_pop_end = std::clock();

    std::cout << "\nPop time:\n";
    std::cout << "  ft  : " << double(ft_pop_end - ft_pop_start) / CLOCKS_PER_SEC << "s\n";
    std::cout << "  std : " << double(std_pop_end - std_pop_start) / CLOCKS_PER_SEC << "s\n";

    return 0;
}
