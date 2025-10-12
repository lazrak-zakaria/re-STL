
#include <iostream>
#include "../../hash_table.hpp"
#include "../../unordered_set.hpp"

#include <iostream>
#include <unordered_set>
#include <chrono>
#include <random>


class m {
public:
    int data;
    m() { std::cout << "Default constructor\n"; }
    m(const m& other) { std::cout << "Copy constructor\n"; data = other.data; }
    // m(m&& other) noexcept { std::cout << "Move constructor\n"; data = other.data; }

    ~m() { std::cout << "Destructor\n"; }

    bool operator==(const m& other) const { return data == other.data; }
};

namespace std {
    template <>
    struct hash<m> {
        std::size_t operator()(const m& obj) const noexcept {
            return std::hash<int>()(obj.data);
        }
    };
}

int main()
{
    using namespace std::chrono;

    const int N = 10000000; 
    ft::unordered_set<m> st;
    
    st.insert(m());
    ft::unordered_set<m> ftt(st);

    st = st;

    return 0;
}
