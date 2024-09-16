#pragma once
#include <vector>

inline int TimeRequiredToBuy(std::vector<int>& tickets, int k) {
    int time = 0;

    const int& ticket = tickets[k];
    while (ticket > 0) {
        for (size_t i = 0; i <= k; ++i)
            if (tickets[i] > 0) {
                --tickets[i];
                ++time;
            }

        if (ticket == 0)
            break;

        for (size_t i = k + 1; i < tickets.size(); ++i) {
            if (tickets[i] > 0) {
                --tickets[i];
                ++time;
            }
        }
    }

    return time;
}
