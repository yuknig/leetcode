#pragma once
#include <cassert>
#include <deque>
#include <vector>
#include <string>


bool CheckValidString(std::string s) {

    int depth = 0;
    int wildCards = 0;

    for (const char ch : s) {
        if (ch == '(')
            ++depth;
        else if (ch == ')') {
            --depth;
            if (depth < 0) {
                if (!wildCards)
                    return false;

                --wildCards;
                ++depth;
            }
        }
        else if (ch == '*') {
            ++wildCards;
        }
    }

    if (!depth)
        return true;

    assert(depth > 0);

    depth = 0;
    wildCards = 0;

    for (auto it = s.crbegin(); it != s.crend(); ++it) {
        const char ch = *it;

        if (ch == ')')
            ++depth;
        else if (ch == '(') {
            --depth;
            if (depth < 0) {
                if (!wildCards)
                    return false;

                --wildCards;
                ++depth;
            }
        }
        else if (ch == '*') {
            ++wildCards;
        }
    }

    return depth >= 0;
}
