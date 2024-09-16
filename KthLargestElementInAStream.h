#pragma once
#include <algorithm>
#include <vector>
#include <set>

class KthLargest {
public:
    KthLargest(int k, std::vector<int> nums)
        : m_k(k)
    {
        if (nums.size() <= k)
        {
            m_values = { nums.begin(), nums.end() };
        }
        else
        {
            std::sort(nums.begin(), nums.end(), std::greater<int>());
            m_values = { nums.begin(), nums.begin() + k };
        }
    }

    int add(int val) {
        m_values.emplace(val);
        if (m_values.size() > m_k)
            m_values.erase(m_values.begin());
        return *(std::prev(m_values.end(), m_k));
    }

    std::multiset<int> m_values;
    int m_k;
};
