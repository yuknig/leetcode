#pragma once
#include <algorithm>
#include <numeric>
#include <vector>

inline int minSubArrayLen(const int target, const std::vector<int>& nums) {

    if (nums.empty())
        return 0;

    int lIdx = 0;
    int rIdx = 0;
    int sum = nums[0];

    int minLen = INT_MAX;

    while (lIdx < nums.size())
    {
        if (sum < target)
        {
            if (rIdx + 1 < static_cast<int>(nums.size()))
                sum += nums[++rIdx];
            else
                break;
        }
        else
        {
            const int curLen = rIdx - lIdx + 1;
            if (curLen < minLen)
            {
                minLen = curLen;
                if (curLen == 1)
                    return curLen;
            }
            sum -= nums[lIdx++];
        }
    }

    return minLen == INT_MAX ? 0 : minLen;
}
