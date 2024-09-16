#pragma once
#include <vector>
#include <algorithm>
#include <numeric>

inline int countTriplets(const std::vector<int>& arr) {
    if (arr.size() <= 1)
        return 0;

    /*const int totalXor = std::accumulate(arr.begin(), arr.end(), 0,
        [](const int lhs, const int rhs) {
            return lhs ^ rhs;
    });*/

    int count = 0;

    for (size_t i = 0; i < arr.size() - 1; ++i)
    {
        int ijXor = 0;

        for (size_t j = i + 1; j < arr.size(); ++j)
        {
            ijXor ^= arr[j - 1];
            int jkXor = 0;
            for (size_t k = j; k < arr.size(); ++k)
            {
                jkXor ^= arr[k];
                if (ijXor == jkXor)
                    ++count;
            }
        }
    }

    return count;
}
