#pragma once
#include <string>

inline int lengthOfLongestSubstring(const std::string& s) {
    int lidx = 0;
    int ridx = 0;
    int maxLen = 0;

    bool hist[256] = { 0 };

    while (ridx < s.size())
    {
        const unsigned char ch = static_cast<unsigned char>(s[ridx]);
        if (!hist[ch])
        {
            hist[ch] = 1;
            ++ridx;
        }
        else
        {
            const int len = ridx - lidx;
            maxLen = std::max(maxLen, len);
            hist[static_cast<unsigned char>(s[lidx])] = 0;
            ++lidx;
        }
    }

    const int len = ridx - lidx;
    maxLen = std::max(maxLen, len);

    return maxLen;
}
