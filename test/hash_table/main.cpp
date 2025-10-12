#include <iostream>
#include <unordered_set>
#include <chrono>
#include <random>
#include "../../unordered_set.hpp" // your custom one

// class t
// {
//     public:
//     class p
//     {
//         private:
//             int k = 5;
//     };

//     void tt()
//     {
//         p pp;
//         std::cout << pp.k << "\n";
//     }
// }

int main() {
    using namespace std;
    using namespace std::chrono;

    const int N = 1'000'000; // adjust for speed

    // Generate random integers
    vector<int> data;
    data.reserve(N);
    mt19937 rng(42); // deterministic
    uniform_int_distribution<int> dist(0, N * 10);

    for (int i = 0; i < N; ++i)
        data.push_back(dist(rng));

    // -------------------------------
    // Insertion Test
    // -------------------------------
    ft::unordered_set<int> ft_set;
    auto start_ft_insert = high_resolution_clock::now();
    for (int v : data)
        ft_set.insert(v);
    auto end_ft_insert = high_resolution_clock::now();
    auto ft_insert_time = duration_cast<milliseconds>(end_ft_insert - start_ft_insert).count();

    std::unordered_set<int> std_set;
    auto start_std_insert = high_resolution_clock::now();
    for (int v : data)
        std_set.insert(v);
    auto end_std_insert = high_resolution_clock::now();
    auto std_insert_time = duration_cast<milliseconds>(end_std_insert - start_std_insert).count();

    // -------------------------------
    // Verify insertion correctness
    // -------------------------------
    bool same = true;
    if (ft_set.size() != std_set.size()) {
        same = false;
    } else {
        for (int v : data) {
            if (ft_set.count(v) != std_set.count(v)) {
                same = false;
                break;
            }
        }
    }

    cout << "=== Insertion test ===\n";
    cout << "ft::unordered_set  : " << ft_insert_time << " ms\n";
    cout << "std::unordered_set : " << std_insert_time << " ms\n";
    cout << "Data identical after insert? " << (same ? "✅ Yes" : "❌ No") << "\n\n";

    // -------------------------------
    // Erase Test (iterator-based)
    // -------------------------------
    auto start_ft_erase = high_resolution_clock::now();
    for (auto it = ft_set.begin(); it != ft_set.end(); ) {
        auto cur = it++;
        ft_set.erase(cur); // erase by iterator
    }
    auto end_ft_erase = high_resolution_clock::now();
    auto ft_erase_time = duration_cast<milliseconds>(end_ft_erase - start_ft_erase).count();

    auto start_std_erase = high_resolution_clock::now();
    for (auto it = std_set.begin(); it != std_set.end(); ) {
        it = std_set.erase(it); // erase returns next iterator
    }
    auto end_std_erase = high_resolution_clock::now();
    auto std_erase_time = duration_cast<milliseconds>(end_std_erase - start_std_erase).count();

    // -------------------------------
    // Verify erasure correctness
    // -------------------------------
    bool same_after_erase = (ft_set.size() == std_set.size());
    if (same_after_erase) {
        same_after_erase = ft_set.empty() && std_set.empty();
    }

    cout << "=== Erase test (iterator-based) ===\n";
    cout << "ft::unordered_set  : " << ft_erase_time << " ms\n";
    cout << "std::unordered_set : " << std_erase_time << " ms\n";
    cout << "Data identical after erase? " << (same_after_erase ? "✅ Yes" : "❌ No") << "\n\n";

    cout << "Final sizes:\n";
    cout << "ft::unordered_set  : " << ft_set.size() << '\n';
    cout << "std::unordered_set : " << std_set.size() << '\n';

    return 0;
}
