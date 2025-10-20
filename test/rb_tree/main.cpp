#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "./../../map.hpp" // your ft::map header

// helper to generate random strings
std::string random_string(size_t len) {
    static const char charset[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string s;
    s.reserve(len);
    for (size_t i = 0; i < len; ++i)
        s.push_back(charset[std::rand() % (sizeof(charset) - 1)]);
    return s;
}

int main() {
    std::srand(std::time(NULL));

    ft::map<int, std::string> ft_m;
    std::map<int, std::string> std_m;

    const int N = 100;
    std::vector<std::pair<int, std::string> > data;

    // Generate random data
    for (int i = 0; i < N; ++i) {
        int key = std::rand() % 500;
        std::string value = random_string(5);
        data.push_back(std::make_pair(key, value));
    }

    bool pass = true;

    // ✅ 1. Test single insert (returns ft::pair)
    std::cout << "Testing single insert...\n";
    for (size_t i = 0; i < data.size(); ++i) {
        ft::pair<ft::map<int, std::string>::iterator, bool> ft_result = 
            ft_m.insert(data[i]);
        std::pair<std::map<int, std::string>::iterator, bool> std_result = 
            std_m.insert(data[i]);

        if (ft_result.second != std_result.second) {
            std::cout << "❌ insert return value mismatch for key: " << data[i].first << "\n";
            pass = false;
            break;
        }

        if (ft_result.first->first != std_result.first->first) {
            std::cout << "❌ insert iterator mismatch for key: " << data[i].first << "\n";
            pass = false;
            break;
        }
    }

    // ✅ 2. Test range insert
    std::cout << "Testing range insert...\n";
    ft::map<int, std::string> ft_m2;
    std::map<int, std::string> std_m2;

    std::vector<std::pair<int, std::string> > range_data;
    for (int i = 0; i < 50; ++i) {
        int key = 1000 + std::rand() % 200;
        std::string value = random_string(4);
        range_data.push_back(std::make_pair(key, value));
    }

    ft_m2.insert(range_data.begin(), range_data.end());
    std_m2.insert(range_data.begin(), range_data.end());

    if (ft_m2.size() != std_m2.size()) {
        std::cout << "❌ range insert size mismatch (ft: " << ft_m2.size() 
                  << ", std: " << std_m2.size() << ")\n";
        pass = false;
    }

    // Verify all elements
    std::map<int, std::string>::iterator std_it = std_m2.begin();
    ft::map<int, std::string>::iterator ft_it = ft_m2.begin();
    while (std_it != std_m2.end() && ft_it != ft_m2.end()) {
        if (ft_it->first != std_it->first || ft_it->second != std_it->second) {
            std::cout << "❌ range insert content mismatch\n";
            pass = false;
            break;
        }
        ++std_it;
        ++ft_it;
    }

    // ✅ 3. Test lower_bound
    std::cout << "Testing lower_bound...\n";
    for (int i = 0; i < 50; ++i) {
        int key = std::rand() % 600;
        
        ft::map<int, std::string>::iterator ft_lb = ft_m.lower_bound(key);
        std::map<int, std::string>::iterator std_lb = std_m.lower_bound(key);

        bool ft_end = (ft_lb == ft_m.end());
        bool std_end = (std_lb == std_m.end());

        if (ft_end != std_end) {
            std::cout << "❌ lower_bound end() mismatch for key: " << key << "\n";
            pass = false;
            break;
        }

        if (!ft_end && ft_lb->first != std_lb->first) {
            std::cout << "❌ lower_bound result mismatch for key: " << key 
                      << " (ft: " << ft_lb->first << ", std: " << std_lb->first << ")\n";
            pass = false;
            break;
        }
    }

    // ✅ 4. Test upper_bound
    std::cout << "Testing upper_bound...\n";
    for (int i = 0; i < 50; ++i) {
        int key = std::rand() % 600;
        
        ft::map<int, std::string>::iterator ft_ub = ft_m.upper_bound(key);
        std::map<int, std::string>::iterator std_ub = std_m.upper_bound(key);

        bool ft_end = (ft_ub == ft_m.end());
        bool std_end = (std_ub == std_m.end());

        if (ft_end != std_end) {
            std::cout << "❌ upper_bound end() mismatch for key: " << key << "\n";
            pass = false;
            break;
        }

        if (!ft_end && ft_ub->first != std_ub->first) {
            std::cout << "❌ upper_bound result mismatch for key: " << key 
                      << " (ft: " << ft_ub->first << ", std: " << std_ub->first << ")\n";
            pass = false;
            break;
        }
    }

    // ✅ 5. Test equal_range (returns ft::pair)
    std::cout << "Testing equal_range...\n";
    for (int i = 0; i < 50; ++i) {
        int key = std::rand() % 600;
        
        ft::pair<ft::map<int, std::string>::iterator, 
                 ft::map<int, std::string>::iterator> ft_er = ft_m.equal_range(key);
        std::pair<std::map<int, std::string>::iterator, 
                  std::map<int, std::string>::iterator> std_er = std_m.equal_range(key);

        bool ft_first_end = (ft_er.first == ft_m.end());
        bool std_first_end = (std_er.first == std_m.end());
        bool ft_second_end = (ft_er.second == ft_m.end());
        bool std_second_end = (std_er.second == std_m.end());

        if (ft_first_end != std_first_end || ft_second_end != std_second_end) {
            std::cout << "❌ equal_range end() mismatch for key: " << key << "\n";
            pass = false;
            break;
        }

        if (!ft_first_end && ft_er.first->first != std_er.first->first) {
            std::cout << "❌ equal_range first mismatch for key: " << key << "\n";
            pass = false;
            break;
        }

        if (!ft_second_end && ft_er.second->first != std_er.second->first) {
            std::cout << "❌ equal_range second mismatch for key: " << key << "\n";
            pass = false;
            break;
        }
    }

    // ✅ 6. Test boundary conditions
    std::cout << "Testing boundary conditions...\n";
    if (!ft_m.empty() && !std_m.empty()) {
        int min_key = std_m.begin()->first;
        int max_key = std_m.rbegin()->first;

        // lower_bound of min should be begin
        ft::map<int, std::string>::iterator ft_lb_min = ft_m.lower_bound(min_key);
        if (ft_lb_min != ft_m.begin()) {
            std::cout << "❌ lower_bound(min) != begin()\n";
            pass = false;
        }

        // upper_bound of max should be end
        ft::map<int, std::string>::iterator ft_ub_max = ft_m.upper_bound(max_key);
        if (ft_ub_max != ft_m.end()) {
            std::cout << "❌ upper_bound(max) != end()\n";
            pass = false;
        }

        // lower_bound of very large key should be end
        ft::map<int, std::string>::iterator ft_lb_large = ft_m.lower_bound(999999);
        if (ft_lb_large != ft_m.end()) {
            std::cout << "❌ lower_bound(huge) != end()\n";
            pass = false;
        }

        // upper_bound of very small key should be begin
        ft::map<int, std::string>::iterator ft_ub_small = ft_m.upper_bound(-999999);
        if (ft_ub_small != ft_m.begin()) {
            std::cout << "❌ upper_bound(tiny) != begin()\n";
            pass = false;
        }
    }

    if (pass)
        std::cout << "✅ All range and bound tests passed!\n";
    else
        std::cout << "❌ Some tests failed.\n";

    return 0;
}