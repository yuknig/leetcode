#pragma once
#include <array>
#include <string>
#include <unordered_map>
#include <vector>

using CharHist = std::array<uint16_t, 26>;

constexpr uint8_t CharCode(char ch)
{
    return ch - 'a';
}

CharHist GetHist(const std::string_view& sv)
{
    CharHist result = {};
    for (char ch : sv)
        ++result[CharCode(ch)];
    return result;
}


template <>
struct std::hash<CharHist>
{
    size_t operator()(const CharHist& hist) const
    {
        size_t result = hist[0];
        for (size_t i = 1; i < 26; ++i)
            result = (result << 2) ^ hist[i];
        return result;
    }
};


class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
        std::unordered_map<CharHist, std::vector<std::string>> groups;
        for (auto&& str : strs)
        {
            const auto key = GetHist(str);
            groups[key].push_back(std::move(str));
        }        

        std::vector<std::vector<std::string>> result;
        result.reserve(groups.size());
        for (auto&& [key, group] : groups)
            result.push_back(std::move(group));
        return result;
    }
};
