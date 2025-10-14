#include <iostream>
#include <unordered_map>
#include <string>
#include <ctime>
#include "../../unordered_map.hpp" // your ft::unordered_map

int main() {
    const int N = 100000; // number of elements
    ft::unordered_map<int, std::string> ft_map;
    std::unordered_map<int, std::string> std_map;

    // Fill maps
    for (int i = 0; i < N; ++i) {
        ft_map.insert(std::make_pair(i, "value" + std::to_string(i)));
        std_map.insert(std::make_pair(i, "value" + std::to_string(i)));
    }

    // 1. Test size
    if (ft_map.size() == std_map.size())
        std::cout << "Size test: PASS\n";
    else
        std::cout << "Size test: FAIL\n";

    // 2. Test count / existence
    bool count_ok = true;
    for (int i = 0; i < N; ++i) {
        if (ft_map.count(i) != std_map.count(i)) {
            count_ok = false;
            break;
        }
    }
    std::cout << "Count test: " << (count_ok ? "PASS" : "FAIL") << "\n";

    // 3. Test erase
    ft_map.erase(N/2);
    std_map.erase(N/2);
    bool erase_ok = (ft_map.count(N/2) == std_map.count(N/2));
    std::cout << "Erase test: " << (erase_ok ? "PASS" : "FAIL") << "\n";

    // 4. Test clear
    ft_map.clear();
    std_map.clear();
    std::cout << "Clear test: " 
              << ((ft_map.empty() && std_map.empty()) ? "PASS" : "FAIL") 
              << "\n";

    // 5. Test re-insert after clear
    ft_map.insert(std::make_pair(1, "new_value"));
    std_map.insert(std::make_pair(1, "new_value"));
    bool reinsertion_ok = (ft_map.find(1)->second == std_map.find(1)->second);
    std::cout << "Re-insertion test: " << (reinsertion_ok ? "PASS" : "FAIL") << "\n";

    // 6. Test iteration values
    ft_map.insert(std::make_pair(2, "two"));
    std_map.insert(std::make_pair(2, "two"));
    bool iteration_ok = true;
    for (auto it = ft_map.begin(); it != ft_map.end(); ++it) {
        auto std_it = std_map.find(it->first);
        if (std_it == std_map.end() || std_it->second != it->second) {
            iteration_ok = false;
            break;
        }
    }
    std::cout << "Iteration values test: " << (iteration_ok ? "PASS" : "FAIL") << "\n";

    return 0;
}
