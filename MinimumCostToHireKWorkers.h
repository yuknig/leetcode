#pragma once
#include <algorithm>
#include <numeric>
#include <map>
#include <vector>

inline double mincostToHireWorkers(const std::vector<int>& quality, const std::vector<int>& wage, int k) {

    if (k == 1)
        return *std::min_element(wage.begin(), wage.end());

    if (k == static_cast<int>(quality.size())) {
        const int qualitySum = std::accumulate(quality.begin(), quality.end(), 0);
        double maxRatio = static_cast<double>(wage[0]) / quality[0];
        for (size_t i = 1; i < quality.size(); ++i)
            maxRatio = std::max(maxRatio, static_cast<double>(wage[i]) / quality[i]);
        return qualitySum * maxRatio;
    }

    std::vector<uint16_t> orderRatio(quality.size());
    std::iota(orderRatio.begin(), orderRatio.end(), 0);

    auto orderQuality = orderRatio;

    std::sort(orderRatio.begin(), orderRatio.end(),
        [&](uint16_t lhs, uint16_t rhs) {
            auto lRatio = static_cast<double>(wage[lhs]) / quality[lhs];
            auto rRatio = static_cast<double>(wage[rhs]) / quality[rhs];
            return lRatio < rRatio;
    });

    std::sort(orderQuality.begin(), orderQuality.end(),
        [&](const uint16_t lhs, const uint16_t rhs) {
            return quality[lhs] < quality[rhs];
    });

    std::vector<double> ratioArr;
    for (size_t i = 0; i < quality.size(); ++i)
        ratioArr.push_back(static_cast<double>(wage[i]) / quality[i]);

    int qualitySum = 0;
    double ratio = 0;

    auto CheckRatio = [&](int sortedIdx) -> int {
        const auto unsortedIdx = orderRatio[sortedIdx];
        ratio = static_cast<double>(wage[unsortedIdx]) / quality[unsortedIdx];

        int count = 0;
        qualitySum = 0;
        for (uint16_t idx : orderQuality) {
            const auto curRatio = static_cast<double>(wage[idx]) / quality[idx];
            if (curRatio > ratio)
                continue;

            qualitySum += quality[idx];
            ++count;
            if (count == k)
                return k;
        }

        return count;
    };

    int l = 0;// k;
    int r = static_cast<int>(orderRatio.size());
    int count = 0;
    while (l < r) {
        const int mid = (l + r) / 2;

        count = CheckRatio(mid);

        if (count < k)
            l = mid + 1;
        else
            r = mid;
    }

    if (count < k)
        count = CheckRatio(l);

    return qualitySum * ratio;
}
