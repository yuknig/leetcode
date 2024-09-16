#pragma once
#include <array>
#include <string>
#include <vector>

auto ParseVersion(const std::string& str) {
    std::vector<int> result(1, 0);

    for (const char ch : str) {
        const int digit = ch - '0';
        if (digit >= 0 && digit <= 9)
            result.back() = result.back() * 10 + digit;
        else if (ch == '.')
            result.push_back(0);
    }

    return result;
}

inline int compareVersion(const std::string& version1, const std::string& version2) {

    auto lhs = ParseVersion(version1);
    auto rhs = ParseVersion(version2);
    const auto length = std::max(lhs.size(), rhs.size());
    lhs.resize(length, 0);
    rhs.resize(length, 0);
    const auto cmpRes = std::lexicographical_compare_three_way(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    if (cmpRes == std::strong_ordering::less)
        return -1;
    if (cmpRes == std::strong_ordering::greater)
        return 1;
    return 0;
}
