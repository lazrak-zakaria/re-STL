#include <iostream>
#include <unordered_map>
#include <ctime>
#include "../../unordered_map.hpp"

bool compare_maps(ft::unordered_map<int, int>& ft_map, std::unordered_map<int, int>& std_map)
{
    if (ft_map.size() != std_map.size()) return false;
    for (std::unordered_map<int, int>::iterator it = std_map.begin(); it != std_map.end(); ++it)
        if (ft_map.count(it->first) == 0 || ft_map.find(it->first)->second != it->second)
            return false;
    return true;
}

int main()
{
    const int N = 2000000;
    ft::unordered_map<int, int> ft_map;
    std::unordered_map<int, int> std_map;

    std::clock_t start, end;
    double ft_time, std_time;

    // INSERT
    start = std::clock();
    for (int i = 0; i < N; ++i)
        ft_map.insert(std::make_pair(i, i));
    end = std::clock();
    ft_time = double(end - start) / CLOCKS_PER_SEC;

    start = std::clock();
    for (int i = 0; i < N; ++i)
        std_map.insert(std::make_pair(i, i));
    end = std::clock();
    std_time = double(end - start) / CLOCKS_PER_SEC;

    std::cout << "Insert: ft=" << ft_time << "s  std=" << std_time << "s\n";

    // FIND
    start = std::clock();
    for (int i = 0; i < N; ++i) ft_map.find(i);
    end = std::clock();
    ft_time = double(end - start) / CLOCKS_PER_SEC;

    start = std::clock();
    for (int i = 0; i < N; ++i) std_map.find(i);
    end = std::clock();
    std_time = double(end - start) / CLOCKS_PER_SEC;

    std::cout << "Find:   ft=" << ft_time << "s  std=" << std_time << "s\n";

    // ERASE
    start = std::clock();
    for (int i = 0; i < N; ++i) ft_map.erase(i);
    end = std::clock();
    ft_time = double(end - start) / CLOCKS_PER_SEC;

    start = std::clock();
    for (int i = 0; i < N; ++i) std_map.erase(i);
    end = std::clock();
    std_time = double(end - start) / CLOCKS_PER_SEC;

    std::cout << "Erase:  ft=" << ft_time << "s  std=" << std_time << "s\n";

    std::cout << (compare_maps(ft_map, std_map) ? "✅ OK\n" : "❌ Mismatch!\n");
}
