#pragma once
#include <algorithm>
#include <unordered_map>
#include <map>
#include <vector>

inline int MaxSubarrayLength(const std::vector<int>& nums, int k) {

    if (k <= 0)
        return 0;

    int maxLength = 0;

    size_t first = 0;
    size_t last= 0;

    std::unordered_map<int, int> freq;
    while (last < nums.size()) {
        int n = nums[last];
        auto& f = freq[n];
        if (f < k) {
            ++f;
            ++last;
            maxLength = std::max(maxLength, static_cast<int>(last - first));
        }
        else if (first < last) {
            --freq[nums[first]];
            ++first;
        }
        else {
            first = last;
        }
    }

    /*for (size_t i = 0; i < nums.size(); ++i) {
        std::map<int, int> freq;
        curLength = 0;
        for (size_t j = i; j < nums.size(); ++j) {
            const int n = nums[j];
            const auto f = ++freq[n];
            if (f <= k) {
                ++curLength;
                maxLength = std::max(maxLength, curLength);
            }
            else
                break;
        }
    }*/

    return maxLength;
}
