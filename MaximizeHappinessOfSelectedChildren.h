#pragma once
#include <algorithm>
#include <vector>

inline long long maximumHappinessSum(std::vector<int>& happiness, int k) {
    k = std::min(k, static_cast<int>(happiness.size()));
    std::partial_sort(happiness.begin(), happiness.begin() + k, happiness.end(),
        [](int lhs, int rhs) {
            return lhs > rhs;
        });

    long long sum = 0;
    for (int turn = 0; turn < k; ++turn) {
        const int curHappiness = std::max(0, happiness[turn] - turn);
        sum += curHappiness;
    }

    return sum;
}
