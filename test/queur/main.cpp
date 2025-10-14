#include <iostream>
#include <queue>
#include <vector>
#include <ctime>
#include "../../queue.hpp"  // your ft::priority_queue

int main() {
    // const int N = 1'000'000; // 1 million elements
    // std::vector<int> data;
    // data.reserve(N);
    // for (int i = 0; i < N; ++i)
    //     data.push_back(i % 10000 - 5000); // deterministic pattern, repeats -5000..4999

    // // ---------------- ft::priority_queue ----------------
    // ft::priority_queue<int> ft_q;
    // clock_t ft_insert_start = std::clock();
    // for (int v : data)
    //     ft_q.push(v);
    // clock_t ft_insert_end = std::clock();

    // // Copy for test
    // ft::priority_queue<int> ft_copy = ft_q;

    // // ---------------- std::priority_queue ----------------
    // std::priority_queue<int> std_q;
    // clock_t std_insert_start = std::clock();
    // for (int v : data)
    //     std_q.push(v);
    // clock_t std_insert_end = std::clock();

    // // ---------------- Check correctness ----------------
    // bool ok = true;
    // while (!ft_q.empty() && !std_q.empty()) {
    //     if (ft_q.top() != std_q.top()) {
    //         ok = false;
    //         std::cerr << "❌ Mismatch at element: ft=" 
    //                   << ft_q.top() << " std=" << std_q.top() << "\n";
    //         break;
    //     }
    //     ft_q.pop();
    //     std_q.pop();
    // }

    // if (ft_q.empty() != std_q.empty()) ok = false;

    // // ---------------- Pop time benchmark ----------------
    // clock_t ft_pop_start = std::clock();
    // while (!ft_copy.empty()) ft_copy.pop();
    // clock_t ft_pop_end = std::clock();

    // // Pop std
    // std::priority_queue<int> std_copy = std_q;
    // clock_t std_pop_start = std::clock();
    // while (!std_copy.empty()) std_copy.pop();
    // clock_t std_pop_end = std::clock();

    // // ---------------- Results ----------------
    // std::cout << "==== PRIORITY_QUEUE BENCHMARK ====\n";
    // std::cout << "Elements: " << N << "\n\n";

    // std::cout << "Insertion time:\n";
    // std::cout << "  ft  : " << double(ft_insert_end - ft_insert_start) / CLOCKS_PER_SEC << "s\n";
    // std::cout << "  std : " << double(std_insert_end - std_insert_start) / CLOCKS_PER_SEC << "s\n\n";

    // std::cout << "Pop time:\n";
    // std::cout << "  ft  : " << double(ft_pop_end - ft_pop_start) / CLOCKS_PER_SEC << "s\n";
    // std::cout << "  std : " << double(std_pop_end - std_pop_start) / CLOCKS_PER_SEC << "s\n\n";

    // std::cout << (ok ? "✅ Results match exactly\n" : "❌ Priority order mismatch\n");

    return 0;
}
