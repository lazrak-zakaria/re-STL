#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <ctime>
#include "../../vector.hpp" // your ft::vector

template <typename T>
bool compare_vectors(const ft::vector<T>& ft_vec, const std::vector<T>& std_vec)
{
    if (ft_vec.size() != std_vec.size())
        return false;
    for (size_t i = 0; i < ft_vec.size(); ++i)
        if (ft_vec[i] != std_vec[i])
            return false;
    return true;
}

template <typename T>
void test_vector_type(const std::string& type_name, const std::vector<T>& sample)
{
    const int N = 500000; // 500k elements
    std::cout << "\n=== Testing type: " << type_name << " (" << N << " elements) ===\n";

    ft::vector<T> ft_vec;
    std::vector<T> std_vec;

    // ---------------- ft::vector ----------------
    clock_t ft_start = clock();
    for (int i = 0; i < N; ++i)
        ft_vec.push_back(sample[i % sample.size()]);
    clock_t ft_end = clock();

    // ---------------- std::vector ----------------
    clock_t std_start = clock();
    for (int i = 0; i < N; ++i)
        std_vec.push_back(sample[i % sample.size()]);
    clock_t std_end = clock();

    double ft_time = double(ft_end - ft_start) / CLOCKS_PER_SEC;
    double std_time = double(std_end - std_start) / CLOCKS_PER_SEC;

    std::cout << "ft::vector time  : " << ft_time << " s\n";
    std::cout << "std::vector time : " << std_time << " s\n";
    std::cout << "Speed ratio      : " << (ft_time / std_time) << "x\n";

    // Integrity
    std::cout << "[Data integrity] "
              << (compare_vectors(ft_vec, std_vec) ? "PASS" : "FAIL") << "\n";
}

int main()
{
    // -------- int test --------
    {
        std::vector<int> sample;
        for (int i = 0; i < 10; ++i) sample.push_back(i);
        test_vector_type("int", sample);
    }

    // -------- std::string test --------
    {
        std::vector<std::string> sample = {
            "hello", "vector", "performance", "test", "ft", "std", "compare"};
        test_vector_type("std::string", sample);
    }

    // -------- std::pair<int, double> test --------
    {
        std::vector<std::pair<int, double>> sample;
        for (int i = 0; i < 10; ++i)
            sample.push_back(std::make_pair(i, i * 0.5));
        test_vector_type("std::pair<int,double>", sample);
    }

    return 0;
}
