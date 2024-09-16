#pragma once
#include <unordered_map>
#include <vector>
//https://leetcode.com/problems/two-sum/

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int, uint16_t> m;
        for (uint16_t i = 0; i < static_cast<uint16_t>(nums.size()); ++i)
            m.emplace(nums[i], i);

        for (int i = 0; i < static_cast<int>(nums.size()); ++i)
        {
            const int n = nums[i];
            const int r = target - n;
            auto findIt = m.find(r);
            if (findIt != m.end() && i != findIt->second)
            {
                std::vector<int> result(2);
                result[0] = i;
                result[1] = findIt->second;
                return result;
            }
        }

        return {};
    }
};
