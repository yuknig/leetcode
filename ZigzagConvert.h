#pragma once
#include <string>

inline std::string ZigZagConvert(const std::string& s, int numRows) {

    if (numRows == 1)
        return s;

    std::string result;
    result.reserve(s.size());

    const int colInc1 = (numRows - 2) * 2 + 2;

    for (int y = 0; y < numRows; ++y) {
        int offset = y;
        if (y == 0 || y == numRows - 1) {
            while (offset < s.size()) {
                result += s[offset];
                offset += colInc1;
            }
        }
        else {
            const int colInc2_1 = (numRows - y - 1) * 2;
            const int colInc2_2 = y * 2;
            while (offset < s.size()) {
                result += s[offset];
                offset += colInc2_1;
                if (offset < s.size()) {
                    result += s[offset];
                    offset += colInc2_2;
                }
            }
        }
    }

    return result;
}