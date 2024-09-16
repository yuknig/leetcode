#pragma once
#include <algorithm>
#include <numeric>
#include <vector>
// https://leetcode.com/problems/contains-duplicate-ii

class Solution {
public:
    bool containsNearbyDuplicate(std::vector<int>& nums, int k) {

        std::vector<uint32_t> order(nums.size());
        std::iota(order.begin(), order.end(), 0);
        std::sort(order.begin(), order.end(),
            [&](uint32_t lhs, uint32_t rhs) {
                return std::tie(nums[lhs], lhs) < std::tie(nums[rhs], rhs);
            });

        for (size_t i = 1; i < order.size(); ++i)
        {
            const auto oLhs = order[i-1];
            const auto oRhs = order[i];
            if (nums[oLhs] == nums[oRhs] && oRhs - oLhs <= k)
                return true;
        }

        //size_t valueStartIdx = 0;
        //while (valueStartIdx < order.size())
        //{
        //    const int value = nums[order[valueStartIdx]];

        //    size_t valueEndIdx = valueStartIdx + 1;
        //    while (valueEndIdx < order.size() && nums[order[valueEndIdx]] == value)
        //    {
        //        ++valueEndIdx;
        //    }

        //    const auto dist = order[valueEndIdx-1] - order[valueStartIdx];
        //    if (dist >= k)
        //        return true;

        //    valueStartIdx = valueEndIdx;
        //}

        return false;
    }
};
