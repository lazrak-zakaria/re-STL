#include <iostream>
#include <unordered_set>    // for std::unordered_set
#include <ctime>            // for std::clock()
#include <cstdlib>          // for std::rand()
#include "../../unordered_set.hpp"  // Include your custom ft::unordered_set

bool compare_sets(ft::unordered_set<int>& ft_set, std::unordered_set<int>& std_set)
{
    if (ft_set.size() != std_set.size())
        return false;

    for (std::unordered_set<int>::iterator it = std_set.begin(); it != std_set.end(); ++it)
        if (ft_set.count(*it) != std_set.count(*it))  // Compare counts for duplicates
            return false;

    return true;
}

int main()
{
    const int N = 2000000; // 2 million elements
    std::cout << "=== Timing Test: ft::unordered_set vs std::unordered_set ===\n";
    std::cout << "Inserting " << N << " integers...\n\n";

    ft::unordered_set<int> ft_set;
    std::unordered_set<int> std_set;

    // ------------------ INSERT TEST ------------------
    std::clock_t start, end;
    double ft_time, std_time;

    start = std::clock();
    for (int i = 0; i < N; ++i)
        ft_set.insert(i);  // Insert in custom unordered set
    end = std::clock();
    ft_time = double(end - start) / CLOCKS_PER_SEC;

    start = std::clock();
    for (int i = 0; i < N; ++i)
        std_set.insert(i); // Insert in standard unordered set
    end = std::clock();
    std_time = double(end - start) / CLOCKS_PER_SEC;

    std::cout << "Insertion time:\n";
    std::cout << "  ft::unordered_set   = " << ft_time << " sec\n";
    std::cout << "  std::unordered_set  = " << std_time << " sec\n";

    if (compare_sets(ft_set, std_set))
        std::cout << "✅ Data check after insertion: OK\n\n";
    else
        std::cout << "❌ Data mismatch after insertion!\n\n";

    // ------------------ FIND TEST ------------------
    std::cout << "Testing find() for all elements...\n";

    start = std::clock();
    for (int i = 0; i < N; ++i)
        ft_set.find(i);  // Find in custom unordered set
    end = std::clock();
    ft_time = double(end - start) / CLOCKS_PER_SEC;

    start = std::clock();
    for (int i = 0; i < N; ++i)
        std_set.find(i); // Find in standard unordered set
    end = std::clock();
    std_time = double(end - start) / CLOCKS_PER_SEC;

    std::cout << "Find time:\n";
    std::cout << "  ft::unordered_set   = " << ft_time << " sec\n";
    std::cout << "  std::unordered_set  = " << std_time << " sec\n\n";




// ------------------ EQUAL_RANGE TEST ------------------
std::cout << "Testing equal_range() for all elements...\n";

start = std::clock();
for (int i = 0; i < N; ++i) {
    ft::unordered_set<int>::iterator it_pair[2];
    it_pair[0] = ft_set.equal_range(i).first;
    it_pair[1] = ft_set.equal_range(i).second;
    // optional: access value to prevent compiler optimizing away
    if (it_pair[0] != it_pair[1])
        volatile int x = *it_pair[0]; 
}
end = std::clock();
ft_time = double(end - start) / CLOCKS_PER_SEC;

start = std::clock();
for (int i = 0; i < N; ++i) {
    std::pair<std::unordered_set<int>::iterator,
              std::unordered_set<int>::iterator> it_pair;
    it_pair = std_set.equal_range(i);
    if (it_pair.first != it_pair.second)
        volatile int x = *it_pair.first;
}
end = std::clock();
std_time = double(end - start) / CLOCKS_PER_SEC;

std::cout << "Equal_range time:\n";
std::cout << "  ft::unordered_set   = " << ft_time << " sec\n";
std::cout << "  std::unordered_set  = " << std_time << " sec\n\n";


    std::cout << "\n=== Done ===\n";
    return 0;
}
