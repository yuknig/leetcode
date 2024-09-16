#pragma once
#include <algorithm>
#include <vector>
#include <unordered_set>

std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    if (nums.empty())
        return {};

    auto ge0it = std::lower_bound(nums.begin(), nums.end(), 0);
    if (ge0it == nums.end())
        return {};

    std::set<std::vector<int>> result;

    if (*ge0it == 0) {
        const auto distFromZeroToEnd = std::distance(ge0it, nums.end());
        if (distFromZeroToEnd >= 3) {
            if (*std::next(ge0it, 1) == 0 &&
                *std::next(ge0it, 2) == 0) {
                result.emplace(3, 0);
            }
        }
    }

    std::vector<int> v(3);

    // One negative number, 2 non negative
    int lastNumber = INT_MAX;
    for (auto negIt = nums.begin(); negIt != ge0it; ++negIt) {
        const int curNegNum = *negIt;
        if (curNegNum == std::exchange(lastNumber, curNegNum))
            continue;

        for (auto nonNegIt = ge0it; nonNegIt != nums.end(); ++nonNegIt) {
            const int curNonNegNum = *nonNegIt;

            const int nonNegRestRest = - (curNegNum + curNonNegNum);
            if (nonNegRestRest < 0)
                continue;

            if (std::binary_search(std::next(nonNegIt), nums.end(), nonNegRestRest)) {
                v[0] = curNegNum;
                v[1] = curNonNegNum;
                v[2] = nonNegRestRest;
                if (v[1] > v[2])
                    std::swap(v[1], v[2]);
                result.emplace(v);
            }
        }
    }

    lastNumber = INT_MAX;

    // One non negative number, 2 negative
    for (auto nonNegIt = ge0it; nonNegIt != nums.end(); ++nonNegIt) {
        const int curNonNegNum = *nonNegIt;
        if (curNonNegNum == std::exchange(lastNumber, curNonNegNum))
            continue;

        for (auto negIt = nums.begin(); negIt != ge0it; ++negIt) {
            const int curNegNum = *negIt;

            const int negRest = -curNonNegNum - curNegNum;
            if (negRest >= 0)
                continue;

            if (std::binary_search(std::next(negIt), ge0it, negRest)) {
                v[0] = curNegNum;
                v[1] = negRest;
                v[2] = curNonNegNum;
                if (v[0] > v[1])
                    std::swap(v[0], v[1]);
                result.emplace(v);
            }
        }
    }

    return { std::move_iterator(result.begin()), std::move_iterator(result.end()) };
}
