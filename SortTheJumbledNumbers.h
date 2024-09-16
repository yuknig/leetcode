#pragma once
#include <algorithm>
#include <cassert>
#include <vector>

std::vector<int> sortJumbled(const std::vector<int>& mapping, std::vector<int> nums) {
    auto Map = [&](int src) {
        static constexpr int pows[] = { 1'000'000'000, 100'000'000, 10'000'000, 1'000'000, 100'000, 10'000, 1000, 100, 10, 1 };

        int dst = 0;

        bool added = false;

        for (auto p : pows)
        {
            const auto srcDigit = src / p;
            assert(srcDigit >= 0);
            assert(srcDigit <= 9);

            if (!srcDigit && !added)
                continue;

            added = true;
            const auto dstDigit = mapping[srcDigit];

            src -= srcDigit * p;
            dst += dstDigit * p;
        }

        return dst;
    };

    std::stable_sort(nums.begin(), nums.end(),
        [&](int lhs, int rhs) {
            const int mappedLhs = Map(lhs);
            const int mappedRhs = Map(rhs);
            return mappedLhs < mappedRhs;
        });

    return nums;
}
