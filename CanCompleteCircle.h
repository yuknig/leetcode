#pragma once
#include <vector>

inline int CanCompleteCircuitImpl(const std::vector<int>& gas, const std::vector<int>& cost) {
    const int length = static_cast<int>(gas.size());

    // find acceptable initial value for startIdx
    int startIdx = -1;
    for (size_t i = 0; i < length; ++i) {
        if (gas[i] >= cost[i]) {
            startIdx = static_cast<int>(i);
            break;
        }
    }
    if (startIdx == -1)
        return -1;

    int endIdx = startIdx;
    int elmsPas = 0;
    int delta = 0;

    while (elmsPas < length) {
        do {
            const int newDelta = delta + gas[endIdx] - cost[endIdx];
            if (newDelta >= 0) {
                delta = newDelta;
                ++elmsPas;
                ++endIdx;
                if (endIdx >= length)
                    endIdx -= length;
            }
            else
                break;
        } while (elmsPas < length);

        while (elmsPas < length) {
            --startIdx;
            if (startIdx < 0)
                startIdx += length;
            ++elmsPas;
            delta += gas[startIdx] - cost[startIdx];
            if (delta >= 0) {
                break;
            }
        }
    }

    return delta >= 0 ? startIdx : -1;
}
