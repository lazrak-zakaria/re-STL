

#include "../min_max_heap.hpp"
#include <vector>

int main() {
    ft::min_max_heap<int, ft::vector<int> , std::greater<int> > heap;
    
    // Insert elements
    std::vector<int> values = {10, 5, 15, 3, 20, 8, 12, 1, 25, 7};
    std::cout << "Inserting: ";
    for (int val : values) {
        std::cout << val << " ";
        heap.push(val);
    }
    std::cout <<"\n" <<heap.pop_max() << "\n";
    std::cout <<"\n" <<heap.pop_max() << "\n";
    std::cout <<"\n" <<heap.pop_max() << "\n";
    std::cout <<"\n" <<heap.pop_max() << "\n";
    return 0;
}