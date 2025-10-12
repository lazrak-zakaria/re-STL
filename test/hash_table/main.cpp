
#include <iostream>
// #include "../../hash_table.hpp"

#include <iostream>
#include <unordered_set>
#include <chrono>

int main()
{
    using namespace std::chrono;

    const int N = 10000000; 


    // {
    //     ft::hash_table<int> ht;

    //     auto start = high_resolution_clock::now();

    //     for (int i = 0; i < N; ++i)
    //         ht._insert(i);

    //     auto end = high_resolution_clock::now();
    //     auto duration = duration_cast<milliseconds>(end - start);

    //     std::cout << "ft::hash_table insert time: " << duration.count() << " ms\n";
    //     start = high_resolution_clock::now();
    //     for (size_t i = 0; i < ht.table.size(); ++i)
    //     {
    //         ft::hash_node<int> *ptr = ht.table[i];
    //         while (ptr)
    //         {   if (ptr->key < 40 )
    //             std::cout <<  ptr->key << "\n";
    //             ptr = ptr->next;
    //         }
    //     }

    //     end = high_resolution_clock::now();
    //     std::cout << "ft::hash_table traversal time: "
    //               << duration_cast<milliseconds>(end - start).count() << " ms\n";
    // }


    {
        std::unordered_set<int> uset;

        // auto start = high_resolution_clock::now();
        uset.max_load_factor(1);
        for (int i = 0; i < 400; ++i)
        {
            std::cout <<uset.bucket_count() << "\n";
            uset.insert(i);
        }
        std::cout << "---------------\n";
        for (int i = 0; i < 400; ++i)
        {
            std::cout <<uset.bucket_count() << "\n";
            uset.erase(uset.begin());
        }

    // auto start = high_resolution_clock::now();

    }

    return 0;
}
