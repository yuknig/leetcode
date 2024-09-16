#pragma once
#include <algorithm>
#include <vector>

class Solution {
public:
    int smallestDistancePair(std::vector<int>& nums, int k) {

        //if (k > static_cast<int>(nums.size()))
        //    return 0;

        std::sort(nums.begin(), nums.end());

        const int dist = FindDist(nums, k);
        return dist;
    }

private:
    static int FindDist(const std::vector<int>& nums, int k)
    {
        const int span = nums.back() - nums.front();

        int minDist = 0;
        int maxDist = span + 1;
        int curDist = 0;

        while (minDist < maxDist)
        {
            curDist = (minDist + maxDist) / 2;
            int count = 0;
            for (size_t i = 0; i < nums.size() - 1; ++i)
            {
                for (size_t j = i + 1; j < nums.size(); ++j)
                {
                    if (nums[j] - nums[i] <= curDist)
                        ++count;
                    else
                        break;
                }
            }

            if (count < k)
                minDist = curDist + 1;
            else /*(count > k)*/
                maxDist = curDist;
        }

        return minDist;
    }
};
