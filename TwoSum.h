#pragma once
#include <algorithm>
#include <vector>

inline std::vector<int> twoSum(const std::vector<int>& numbers, int target) {

    int lastNum = numbers.back();
    for (size_t n = 0; n < numbers.size(); ++n) {
        const int num1 = numbers[n];
        if (lastNum == num1)
            continue;
        lastNum = num1;

        const int num2 = target - num1;
        auto lbIt = std::lower_bound(numbers.cbegin() + n + 1, numbers.cend(), num2);
        if (lbIt == numbers.cend() || *lbIt != num2)
            continue;

        const int n1 = static_cast<int>(n);
        const int n2 = static_cast<int>(lbIt - numbers.cbegin());
        return { n1 + 1, n2 + 1 };
    }

    return {};
}
