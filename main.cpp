#include <iostream>
#include "./vector.hpp"

#include <vector>
int main()
{
    std::vector<int> v;

    ft::vector<int> t;
    t.push_back(6);
    t.push_back(63);
    t.push_back(60);
    t.front()+=1;
    t.print();
    // std::cout <<  << "\n";
    // t.pub = 33;
    // std::cout << t.pub;



    return 0;
}