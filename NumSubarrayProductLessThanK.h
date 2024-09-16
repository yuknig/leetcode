#pragma once
#include <algorithm>
#include <cassert>
#include <vector>

const std::vector<int>* pNums = nullptr;
int K = 0;
int count = 0;

std::vector<std::vector<int>> results;

inline void Walk(const uint16_t curIndex, const int curProduct, std::vector<int> indices) {
    assert(curProduct < K);
    results.push_back(indices);

    ++count;
    const auto nextIndex = curIndex + 1;
    if (nextIndex < static_cast<uint16_t>(pNums->size())) {
        const int curNum = (*pNums)[nextIndex];
        const auto thisProduct = curProduct * curNum;
        if (thisProduct < K)  {
            auto v = indices;
            v.push_back(curNum);
            Walk(nextIndex, thisProduct, v);
        }
    }
}

inline int numSubarrayProductLessThanK(std::vector<int> nums, int k) {
    pNums = &nums;
    K = k;
    count = 0;

    for (uint16_t idx = 0; idx < static_cast<uint16_t>(nums.size()); ++idx) {
        const int curNum = nums[idx];
        if (curNum >= k)
            continue;

        Walk(idx, curNum, std::vector<int>(1, curNum));
    }

    return count;
}
