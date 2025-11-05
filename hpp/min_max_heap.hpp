#include <iostream>
#include "algorithm.hpp"
#include "vector.hpp"
#include "deque.hpp"



// https://www.cs.otago.ac.nz/staffpriv/mike/Papers/MinMaxHeaps/MinMaxHeaps.pdf

namespace ft
{

    template <class T, class Container = ft::vector<T>, class Compare = std::less<typename Container::value_type>  >
    class min_max_heap
    {

    public:
        typedef Container container_type;
        typedef typename Container::value_type value_type;
        typedef Compare value_compare;
        typedef typename Container::size_type size_type;
        typedef typename Container::reference reference;
        typedef typename Container::const_reference const_reference;

    protected:
        container_type C;
        value_compare comp;

    private:
        bool is_min_level(int i) const
        {
            if (i == 0)
                return true;

            int level = 0;
            int pos = i + 1;
            while (pos > 1)
            {
                pos /= 2;
                level++;
            }

            return level % 2 == 0;
        }

        int parent(int i) const
        {
            if (i == 0)
                return -1;
            return (i - 1) / 2;
        }

        int left_child(int i) const
        {
            return 2 * i + 1;
        }

        int right_child(int i) const
        {
            return 2 * i + 2;
        }

        bool has_children(int i)
        {
            return left_child(i) < static_cast<int>(C.size());
        }


        int index_of_smallest(int i)
        {
            int smallest = left_child(i);
            if (smallest >= static_cast<int>(C.size()))
                return -1;

            container_type candidates;
            candidates.push_back(smallest);

            int right = right_child(i);
            if (right < static_cast<int>(C.size()))
            {
                candidates.push_back(right);
            }

            int left = left_child(i);
            if (left < static_cast<int>(C.size()))
            {
                int leftLeft = left_child(left);
                int leftRight = right_child(left);
                if (leftLeft < static_cast<int>(C.size()))
                    candidates.push_back(leftLeft);
                if (leftRight < static_cast<int>(C.size()))
                    candidates.push_back(leftRight);
            }

            if (right < static_cast<int>(C.size()))
            {
                int rightLeft = left_child(right);
                int rightRight = right_child(right);
                if (rightLeft < static_cast<int>(C.size()))
                    candidates.push_back(rightLeft);
                if (rightRight < static_cast<int>(C.size()))
                    candidates.push_back(rightRight);
            }

            int minIdx = candidates[0];
            for (size_t j = 1; j < candidates.size(); j++)
            {

                if (comp(C[candidates[j]], C[minIdx]))
                {
                    minIdx = candidates[j];
                }
            }

            return minIdx;
        }


        int index_of_largest(int i)
        {
            int largest = left_child(i);
            if (largest >= static_cast<int>(C.size()))
                return -1;

            container_type candidates;
            candidates.push_back(largest);

            int right = right_child(i);
            if (right < static_cast<int>(C.size()))
            {
                candidates.push_back(right);
            }

            int left = left_child(i);
            if (left < static_cast<int>(C.size()))
            {
                int leftLeft = left_child(left);
                int leftRight = right_child(left);
                if (leftLeft < static_cast<int>(C.size()))
                    candidates.push_back(leftLeft);
                if (leftRight < static_cast<int>(C.size()))
                    candidates.push_back(leftRight);
            }

            if (right < static_cast<int>(C.size()))
            {
                int rightLeft = left_child(right);
                int rightRight = right_child(right);
                if (rightLeft < static_cast<int>(C.size()))
                    candidates.push_back(rightLeft);
                if (rightRight < static_cast<int>(C.size()))
                    candidates.push_back(rightRight);
            }

            int maxIdx = candidates[0];
            for (size_t j = 1; j < candidates.size(); j++)
            {
                
                if (comp(C[maxIdx], C[candidates[j]]))
                {
                    maxIdx = candidates[j];
                }
            }

            return maxIdx;
        }

        bool is_grand_child(int i, int m)
        {
            int p = parent(m);
            if (p < 0)
                return false;
            return parent(p) == i;
        }

        void trickle_down_min(int i)
        {
            if (has_children(i))
            {
                int m = index_of_smallest(i);
                if (m < 0)
                    return;

                if (is_grand_child(i, m))
                {
                    // comp(C[m], C[i]) means C[m] < C[i]
                    if (comp(C[m], C[i]))
                    {
                        ft::swap(C[i], C[m]);
                        int p = parent(m);
                        if (p >= 0 && comp(C[p], C[m]))
                        {
                            ft::swap(C[m], C[p]);
                        }
                        trickle_down_min(m);
                    }
                }
                else
                {
                    // m is a child of i
                    if (comp(C[m], C[i]))
                    {
                        ft::swap(C[i], C[m]);
                    }
                }
            }
        }

        void trickle_down_max(int i)
        {
            if (has_children(i))
            {
                int m = index_of_largest(i);
                if (m < 0)
                    return;

                if (is_grand_child(i, m))
                {
  
                    if (comp(C[i], C[m]))
                    {
                        ft::swap(C[i], C[m]);
                        int p = parent(m);

                        if (p >= 0 && comp(C[m], C[p]))
                        {
                            ft::swap(C[m], C[p]);
                        }
                        trickle_down_max(m);
                    }
                }
                else
                {
                    // m is a child of i
                    if (comp(C[i], C[m]))
                    {
                        ft::swap(C[i], C[m]);
                    }
                }
            }
        }

        void trickle_down(int i)
        {
            if (i >= static_cast<int>(C.size()))
                return;

            if (is_min_level(i))
            {
                trickle_down_min(i);
            }
            else
            {
                trickle_down_max(i);
            }
        }

        void bubble_up_min(int i)
        {
            int p = parent(i);
            if (p >= 0)
            {
                int gp = parent(p);
                if (gp >= 0 && comp(C[i], C[gp]))
                {
                    ft::swap(C[i], C[gp]);
                    bubble_up_min(gp);
                }
            }
        }

        void bubble_up_max(int i)
        {
            int p = parent(i);
            if (p >= 0)
            {
                int gp = parent(p);
                if (gp >= 0 && comp(C[gp], C[i]))
                {
                    ft::swap(C[i], C[gp]);
                    bubble_up_max(gp);
                }
            }
        }

        void bubble_up(int i)
        {
            if (i == 0)
                return;

            int p = parent(i);
            if (p < 0)
                return;

            if (is_min_level(i))
            {
                // On min level
                // comp(C[p], C[i]) means C[p] < C[i], so C[i] > C[p]
                if (comp(C[p], C[i]))
                {
                    ft::swap(C[i], C[p]);
                    bubble_up_max(p);
                }
                else
                    bubble_up_min(i);
            }
            else
            {
                // On max level
                // comp(C[i], C[p]) means C[i] < C[p]
                if (comp(C[i], C[p]))
                {
                    ft::swap(C[i], C[p]);
                    bubble_up_min(p);
                }
                else
                {
                    bubble_up_max(i);
                }
            }
        }

        int index_of_max() const
        {
            if (C.size() == 1)
                return 0;
            if (C.size() == 2)
                return 1;

            return comp(C[1], C[2]) ? 2 : 1;
        }

    public:
        min_max_heap() : comp(Compare()) {}

        explicit min_max_heap(const Compare& c) : comp(c) {}

        min_max_heap(const container_type &arr) : C(arr), comp(Compare())
        {
            if (C.empty())
                return;
            for (int i = static_cast<int>(C.size()) / 2 - 1; i >= 0; i--)
            {
                trickle_down(i);
            }
        }

        min_max_heap(const container_type &arr, const Compare& c) : C(arr), comp(c)
        {
            if (C.empty())
                return;
            for (int i = static_cast<int>(C.size()) / 2 - 1; i >= 0; i--)
            {
                trickle_down(i);
            }
        }

        void push(const value_type& value)
        {
            C.push_back(value);
            bubble_up(C.size() - 1);
        }

        const value_type& min() const
        {
            return C.front();
        }

        const value_type& max() const
        {
            if (C.size() == 1)
                return C[0];
            if (C.size() == 2)
                return C[1];

            return comp(C[1], C[2]) ? C[2] : C[1];
        }

        value_type pop_min()
        {
            value_type minVal = C[0];

            C[0] = C.back();
            C.pop_back();

            if (!C.empty())
            {
                trickle_down(0);
            }

            return minVal;
        }

        value_type pop_max()
        {
            if (C.size() == 1)
            {
                value_type maxVal = C[0];
                C.pop_back();
                return maxVal;
            }

            int maxIdx = index_of_max();
            value_type maxVal = C[maxIdx];

            C[maxIdx] = C.back();
            C.pop_back();

            if (maxIdx < static_cast<int>(C.size()))
            {
                trickle_down(maxIdx);
            }

            return maxVal;
        }

        bool empty() const
        {
            return C.empty();
        }

        size_type size() const
        {
            return C.size();
        }

        void print() const
        {
            std::cout << "Heap: ";
            for (typename container_type::const_iterator it = C.begin(); it != C.end(); ++it)
            {
                std::cout << *it << " ";
            }
            std::cout << std::endl;
        }
    };

}