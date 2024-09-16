#pragma once
#include <bitset>
#include <vector>

inline int firstMissingPositive(const std::vector<int>& nums) {
    constexpr size_t TableSize = 4096;
    std::bitset<TableSize> table;

    for (int iterNum = 0u; iterNum < INT_MAX; ++iterNum) {
        table.reset();
        const int rangeBegin = iterNum*TableSize + 1;
        const int rangeEnd = rangeBegin + TableSize;

        for (int num : nums) {
            if (num >= rangeBegin && num < rangeEnd) {
                const int pos = num - rangeBegin;
                table.set(static_cast<size_t>(pos));
            }
        }

        for (size_t i = 0; i < TableSize; ++i) {
            if (!table[i])
                return rangeBegin + static_cast<int>(i);
        }
    }

    return 1;
}
