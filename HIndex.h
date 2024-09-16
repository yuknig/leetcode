#pragma once
#include <vector>

inline int hIndex(const std::vector<int>& citations) {
    std::vector<int> hist;

    for (int c : citations) {
        if (c >= hist.size())
            hist.resize(c + 1);

        for (int i = 0; i < c; ++i) {
            ++hist[i];
        }
    }

    for (int i = static_cast<int>(hist.size()) - 1; i >= 0; --i) {
        if (hist[i] > i)
            return i + 1;
    }

    return 0;
}
