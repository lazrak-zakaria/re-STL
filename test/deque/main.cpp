#include <iostream>

#include <iomanip> 
using namespace std;
class m
{
public:
    // Default constructor

    int data;
    m()
    {
        std::cout << "Default constructor called" << std::endl;
    }

    // Copy constructor
    m(const m &other)
    {
        std::cout << "Copy constructor called" << std::endl;
    }

    // Destructor
    ~m()
    {
        std::cout << "Destructor called" << std::endl;
    }
};
#include <ctime>     // for clock()
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
#include <map>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "../../deque.hpp"
#include <deque>
int main()
{











 std::cout << "===== TEST: insert(range) — no operator= used =====\n";

    // 1️⃣ Build base deques
    ft::deque<int> ft_t;
    std::deque<int> std_t;
    for (int i = 0; i < 100000; ++i) {
        ft_t.push_back(i);
        std_t.push_back(i);
    }

    // 2️⃣ Build source range
    ft::deque<int> ft_src;
    std::deque<int> std_src;
    for (int i = 0; i < 200; ++i) {
        ft_src.push_back(777 + i);
        std_src.push_back(777 + i);
    }

    // 3️⃣ Define positions to test
    int positions[] = {0, 50, 50000, (int)ft_t.size()};
    size_t n_positions = sizeof(positions) / sizeof(int);

    for (size_t p = 0; p < n_positions; ++p) {
        int pos = positions[p];
        std::cout << "\n👉 Inserting range at position " << pos << "...\n";

        // --- Build manually (no operator=) ---
        ft::deque<int> ft_temp;
        std::deque<int> std_temp;
        for (size_t i = 0; i < ft_t.size(); ++i) {
            ft_temp.push_back(ft_t[i]);
            std_temp.push_back(std_t[i]);
        }

        // --- Perform insert(range) ---
        clock_t start = clock();
        ft_temp.insert(ft_temp.begin() + pos, ft_src.begin(), ft_src.end());
        clock_t end = clock();
        double ft_time = double(end - start) / CLOCKS_PER_SEC;

        start = clock();
        std_temp.insert(std_temp.begin() + pos, std_src.begin(), std_src.end());
        end = clock();
        double std_time = double(end - start) / CLOCKS_PER_SEC;

        // --- Validate ---
        bool ok = true;
        if (ft_temp.size() != std_temp.size()) {
            std::cout << "❌ size mismatch: ft=" << ft_temp.size()
                      << ", std=" << std_temp.size() << "\n";
            ok = false;
        } else {
            for (size_t i = 0; i < ft_temp.size(); ++i) {
                if (ft_temp[i] != std_temp[i]) {
                    std::cout << "❌ mismatch at index " << i 
                              << ": ft=" << ft_temp[i] 
                              << ", std=" << std_temp[i] << "\n";
                    ok = false;
                    break;
                }
            }
        }

        if (ok)
            std::cout << "✅ insert(range) identical to std::deque\n";
        else
            std::cout << "❌ insert(range) content differs\n";

        // --- Print nicely formatted time ---
        std::cout << std::fixed << std::setprecision(6);
        std::cout << "⏱ ft_time=" << ft_time << " s | std_time=" << std_time << " s\n";
    }

    std::cout << "\n===== insert(range) test completed =====\n";










    return 0;
}