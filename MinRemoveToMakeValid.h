#pragma once
#include <string>

bool StringValid(const std::string& s) {
    int depth = 0;
    for (char ch : s) {
        if (ch == '(')
            ++depth;
        else if (ch == ')') {
            --depth;
            if (depth < 0)
                return false;
        }
    }

    return depth == 0;
}

inline std::string minRemoveToMakeValid(std::string s) {

    int depth = 0;

    // remove non matching closing brackets
    {
        depth = 0;
        int pos = 0;
        while (pos < s.size()) {
            const char ch = s[pos];
            if (ch == '(')
                ++depth;
            else if (ch == ')') {
                --depth;
                if (depth < 0) {
                    ++depth;
                    s.erase(pos, 1);
                    continue;
                }
            }

            ++pos;
        }
    }

    // remove non matching open brackets
    {
        depth = 0;
        int pos = static_cast<int>(s.size()) - 1;
        while (pos >= 0) {
            const char ch = s[pos];
            if (ch == ')')
                ++depth;
            else if (ch == '(') {
                --depth;
                if (depth < 0) {
                    ++depth;
                    s.erase(pos, 1);
                }
            }

            --pos;
        }
    }

    return s;
}
