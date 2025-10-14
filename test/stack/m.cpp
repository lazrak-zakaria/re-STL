#include <iostream>
#include <stack>
#include <vector>
#include <ctime>
#include "../../stack.hpp"  // your ft::stack

// Utility to compare stack contents
template <typename T>
bool equal_stacks(ft::stack<T> ft_s, std::stack<T> std_s) {
    if (ft_s.size() != std_s.size()) return false;
    while (!ft_s.empty()) {
        if (ft_s.top() != std_s.top())
            return false;
        ft_s.pop();
        std_s.pop();
    }
    return true;
}

// Utility: print all comparison operators
template <typename S>
void compare_ops(const S& a, const S& b, const std::string& nameA, const std::string& nameB) {
    std::cout << "Comparing " << nameA << " vs " << nameB << ":\n";
    std::cout << "  == " << (a == b) << "\n";
    std::cout << "  != " << (a != b) << "\n";
    std::cout << "  <  " << (a < b)  << "\n";
    std::cout << "  <= " << (a <= b) << "\n";
    std::cout << "  >  " << (a > b)  << "\n";
    std::cout << "  >= " << (a >= b) << "\n\n";
}

int main() {
    const int N = 1'000'000; // 1 million elements for stress test
    std::cout << "==== STACK FUNCTIONAL & STRESS TEST ====\n";
    std::cout << "Elements: " << N << "\n\n";

    // -----------------------------------------------------
    // 1. Insertion performance + correctness
    // -----------------------------------------------------
    ft::stack<int> ft_s;
    std::stack<int> std_s;

    clock_t ft_push_start = std::clock();
    for (int i = 0; i < N; ++i)
        ft_s.push(i);
    clock_t ft_push_end = std::clock();

    clock_t std_push_start = std::clock();
    for (int i = 0; i < N; ++i)
        std_s.push(i);
    clock_t std_push_end = std::clock();

    std::cout << "Push time:\n";
    std::cout << "  ft  : " << double(ft_push_end - ft_push_start) / CLOCKS_PER_SEC << "s\n";
    std::cout << "  std : " << double(std_push_end - std_push_start) / CLOCKS_PER_SEC << "s\n\n";

    // -----------------------------------------------------
    // 2. Functional correctness (top, pop)
    // -----------------------------------------------------
    bool ok = true;
    for (int i = 0; i < 10; ++i) {
        if (ft_s.top() != std_s.top()) {
            ok = false;
            std::cerr << "❌ Mismatch at top(): ft=" << ft_s.top()
                      << " std=" << std_s.top() << "\n";
            break;
        }
        ft_s.pop();
        std_s.pop();
    }

    if (ok)
        std::cout << "✅ Basic top/pop behavior correct\n\n";

    // -----------------------------------------------------
    // 3. Operator comparison test
    // -----------------------------------------------------
    ft::stack<int> ft_a;
    ft::stack<int> ft_b;
    std::stack<int> std_a;
    std::stack<int> std_b;

    for (int i = 0; i < 5; ++i) {
        ft_a.push(i);
        std_a.push(i);
    }

    for (int i = 0; i < 5; ++i) {
        ft_b.push(i);
        std_b.push(i);
    }

    // make them slightly different
    ft_b.push(99);
    std_b.push(99);

    std::cout << "---- Operator comparisons ----\n";
    compare_ops(ft_a, ft_b, "ft_a", "ft_b");
    compare_ops(std_a, std_b, "std_a", "std_b");

    // -----------------------------------------------------
    // 4. Full equality validation
    // -----------------------------------------------------
    ft::stack<int> ft_equal;
    std::stack<int> std_equal;
    for (int i = 0; i < 1000; ++i) {
        ft_equal.push(i * 7);
        std_equal.push(i * 7);
    }

    bool same = equal_stacks(ft_equal, std_equal);
    std::cout << (same ? "✅ All elements identical to std::stack\n"
                       : "❌ Stack contents differ from std::stack\n");

    // -----------------------------------------------------
    // 5. Pop performance
    // -----------------------------------------------------
    ft::stack<int> ft_pop = ft_equal;
    std::stack<int> std_pop = std_equal;

    clock_t ft_pop_start = std::clock();
    while (!ft_pop.empty()) ft_pop.pop();
    clock_t ft_pop_end = std::clock();

    clock_t std_pop_start = std::clock();
    while (!std_pop.empty()) std_pop.pop();
    clock_t std_pop_end = std::clock();

    std::cout << "\nPop time:\n";
    std::cout << "  ft  : " << double(ft_pop_end - ft_pop_start) / CLOCKS_PER_SEC << "s\n";
    std::cout << "  std : " << double(std_pop_end - std_pop_start) / CLOCKS_PER_SEC << "s\n";

    return 0;
}
