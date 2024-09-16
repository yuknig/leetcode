#pragma once
#include <algorithm>
#include <unordered_map>
#include <vector>

inline long long CountSubarrays(const std::vector<int>& nums, int k) {

    const uint32_t Size = static_cast<uint32_t>(nums.size());
    if (static_cast<int>(Size) < k)
        return 0;

    const auto firstMaxIt = std::max_element(nums.begin(), nums.end());
    const int maxV = *firstMaxIt;
    std::vector<uint32_t> maxPos;
    for (uint32_t i = static_cast<uint32_t>(firstMaxIt - nums.begin()); i < Size; ++i) {
        if (nums[i] == maxV)
            maxPos.push_back(i);
    }

    if (maxPos.size() < k)
        return 0;

    const uint32_t lastI = std::min(Size, maxPos[maxPos.size() - k] + 1);

    long long count = 0;
    uint32_t i = 0;
    while (i < lastI) {
        const auto nextIPosIt = std::lower_bound(maxPos.begin(), maxPos.end(), i);
        const uint32_t firtsMaxIth = static_cast<uint32_t>(nextIPosIt - maxPos.begin());
        const uint32_t kIntervalLeft = maxPos[firtsMaxIth];
        const uint32_t kIntervalRight = maxPos[firtsMaxIth + k - 1];
        for (uint32_t c = i; c <= kIntervalLeft; ++c) {
            count += Size - kIntervalRight;
        }
        i = kIntervalLeft + 1;
    }

    return count;
}
