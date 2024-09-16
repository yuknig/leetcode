#pragma once
#include <string>
#include <unordered_map>
#include <vector>
// https://leetcode.com/problems/kth-distinct-string-in-an-array/

inline std::string kthDistinct(const std::vector<std::string>& arr, int k) {
    std::unordered_map<std::string, uint16_t> m;
    for (const auto& s : arr)
    {
        auto [it, added] = m.emplace(s, 1);
        if (!added)
            ++it->second;
    }

    int curK = 0;
    for (const auto& s : arr)
    {
        if (m[s] == 1)
        {
            ++curK;
            if (k == curK)
                return s;
        }
    }

    return "";
}
