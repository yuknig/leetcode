#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>

inline int SubarraysWithKDistinct(const std::vector<int>& nums, int k) {

    if (k <= 0)
        return 0;

    const uint32_t szK = static_cast<uint32_t>(k);
    int count = 0;

    std::unordered_map<int, uint32_t> unique;
    size_t first = 0;
    size_t last = 0;

    while (last < nums.size()) {
        const int n = nums[last];
        auto findIt = unique.find(n);
        if (findIt != unique.end()) {
            if (unique.size() == szK)
                ++count;
            ++findIt->second;
            ++last;
        }
        else if (unique.size() < szK) {
            unique.emplace(n, 1);
            if (unique.size() == szK)
                ++count;
            ++last;
        }
        else {
            auto firstIt = unique.find(nums[first]);
            if (firstIt->second == 1)
                unique.erase(firstIt);
            else
                --firstIt->second;
            ++first;
        }
    }

    //for (int i = 0; i < nums.size(); ++i) {
    //    unique.clear();
    //    for (size_t j = i; j < nums.size(); ++j) {
    //        const int n = nums[j];

    //        unique.emplace(n);
    //        if (unique.size() == szK)
    //            ++count;
    //        else if (unique.size() > szK)
    //            break;
    //    }
    //}

    return count;
}
