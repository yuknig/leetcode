#pragma once
#include <algorithm>
#include <vector>


inline int findDuplicate(const std::vector<int>& nums) {

    int start = 0;
    int end = static_cast<int>(nums.size());
    while (start < end) {
        const int cur = (start + end) / 2;
        const auto count = std::count_if(nums.begin(), nums.end(),
            [&](const int i) {
                return i <= cur;
        });

        if (count > cur)
            end = cur;
        else
            start = cur+1;
    }

    return start;
}
