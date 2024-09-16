#pragma once
#include <algorithm>
#include <tuple>
#include <vector>

using Ratio = std::pair<uint16_t, uint16_t>;


inline std::vector<int> kthSmallestPrimeFraction(const std::vector<int>& arr, int k) {
    std::vector<Ratio> r;
    for (size_t i = 0; i < arr.size(); ++i) {
        for (size_t j = i + 1; j < arr.size(); ++j) {
            r.emplace_back(static_cast<uint16_t>(i), static_cast<uint16_t>(j));
        }
    }

    std::sort(r.begin(), r.end(),
        [&](const Ratio& lhs, const Ratio& rhs) {
            return (static_cast<double>(arr[lhs.first]) / arr[lhs.second]) <
                (static_cast<double>(arr[rhs.first]) / arr[rhs.second]);
        });

    std::vector<int> v;
    v.push_back(arr[r[k-1].first]);
    v.push_back(arr[r[k-1].second]);

    return v;
}
