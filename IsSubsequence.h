#pragma once
#include <string>

inline bool isSubsequence(const std::string& s, const std::string& t) {

    if (s.empty() || t.empty())
        return false;

    const char firstCh = s[0];

    size_t startOffset = 0;
    while (startOffset < t.size()) {
        size_t curOffset = t.find(firstCh, startOffset);
        if (curOffset == std::string::npos)
            return false;

        startOffset = ++curOffset;

        bool found = true;
        for (size_t chNum = 1; chNum < s.size(); ++chNum) {
            const char chToFind = s[chNum];
            auto chPos = t.find(chToFind, curOffset);
            if (chPos == std::string::npos) {
                found = false;
                break;
            }

            curOffset = chPos + 1;
        }
        if (found)
            return true;
    }

    return false;
}
