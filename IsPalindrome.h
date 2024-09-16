#pragma once
#include <string>

void PrepareString(std::string& s)
{
    s.erase(std::remove_if(s.begin(), s.end(), [](char ch) {
        return !isalnum(ch);
    }), s.end());

    for (char& ch : s) {
        if (isupper(ch))
            ch = static_cast<char>(tolower(ch));
    }
}

inline bool isPalindrome(std::string s) {
    PrepareString(s);
    for (size_t c = 0; c < s.size() / 2; ++c) {
        if (s[c] != s[s.size() - c - 1])
            return false;
    }

    return true;
}
