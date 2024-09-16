#pragma once
#include <vector>
#include <string_view>
#include <unordered_map>

class Solution {
public:
    bool wordPattern(const std::string& pattern, const std::string& s) {
        std::array<std::string_view, 26> words;

        size_t num = 0;
        size_t start = 0;
        while (start < s.size())
        {
            if (num >= pattern.size())
                return false;

            size_t end = s.find(' ', start);
            if (end == std::string::npos)
                end = s.size();

            std::string_view curWord(s.data() + start, s.data() + end);
            const char ch = pattern[num++];
            auto& word = words[GetCharCode(ch)];
            if (word.empty())
                word = curWord;
            else if (word != curWord)
                return false;

            start = end + 1;
        }

        if (num < pattern.size())
            return false;

        std::sort(words.begin(), words.end());
        for (size_t i = 1; i < words.size(); ++i)
        {
            if (!words[i].empty() && words[i] == words[i - 1])
                return false;
        }

        return true;
    }

private:
    static constexpr uint8_t GetCharCode(char ch)
    {
        return ch - 'a';
    }
};
