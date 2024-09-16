#pragma once
#include <algorithm>
#include <array>
#include <bitset>
#include <vector>
#include <string>
#include <unordered_map>
#include <intrin.h>

//https://leetcode.com/problems/minimum-cost-to-convert-string-i

constexpr size_t CharCount = 26;
using CharCode = uint8_t;
using CharBitset = std::bitset<CharCount>;
using Cache = std::array<std::array<int, CharCount>, CharCount>;

constexpr CharCode GetCharCode(char ch) {
    return ch - 'a';
}

void InitCache(Cache& cache) {
    for (auto& cc : cache)
        for (auto& c : cc)
            c = 0;
}

class Solution {
public:
    template <size_t Depth>
    bool Visit(const CharCode curChCode) {

        m_curSteps[Depth] = curChCode;
        int curCost = 0;

        for (CharCode d = Depth; d > 0; --d) {
            const CharCode stepFrom = m_curSteps[d - 1];
            const CharCode stepTo = m_curSteps[d];
            const int stepCost = m_rules[stepFrom][stepTo];
            assert(stepCost > 0);

            curCost += stepCost;
            if (d < Depth)
            {
                auto& curCacheValue = m_rules[stepFrom][curChCode];
                if (!curCacheValue || curCacheValue > curCost)
                    curCacheValue = curCost;
            }
        }


        if (curChCode == m_dstCode)
        {
            assert(curCost < m_minCost);
            m_minCost = curCost;
            return true;
        }

        m_visited.set(curChCode);

        const auto& ruleRow = m_rules[curChCode];
        for (CharCode i = 0; i < CharCount; ++i) {
            const auto cost = ruleRow[i];
            if (!cost)
                continue;

            if (m_visited[i])
                continue;

            const auto nextCost = curCost + cost;
            if (nextCost >= m_minCost)
                continue;

            if constexpr (Depth < CharCount)
                Visit<Depth+1>(i);
        }

        m_visited.reset(curChCode);

        return m_minCost != INT_MAX;
    }

    long long getCost(const char from, const char to) {

        const auto codeFrom = GetCharCode(from);
        const auto codeTo = GetCharCode(to);

        auto& finalCacheItem = m_finalCache[codeFrom][codeTo];
        if (finalCacheItem)
            return finalCacheItem;

        const auto curCacheVal = m_rules[codeFrom][codeTo];

        m_dstCode = codeTo;
        m_minCost = curCacheVal ? curCacheVal : INT_MAX;
        //m_visited.reset();
        if (!Visit<0>(codeFrom))
            return -1;

        finalCacheItem = m_minCost;
        return m_minCost;
    }

    long long minimumCost(const std::string& source, const std::string& target, const std::vector<char>& original, const std::vector<char>& changed, const std::vector<int>& cost) {

        InitCache(m_finalCache);
        InitCache(m_rules);

        for (size_t i = 0; i < original.size(); ++i)
        {
            const char srcChCode = GetCharCode(original[i]);
            const char dstChCode = GetCharCode(changed[i]);
            const int curCost = cost[i];

            auto& curCacheItem = m_rules[srcChCode][dstChCode];
            if (!curCacheItem)
                curCacheItem = curCost;
            else
                curCacheItem = std::min(curCacheItem, curCost);
        }

        long long result = 0;

        for (size_t c = 0; c < source.size(); ++c)
        {
            const char srcCh = source[c];
            const char dstCh = target[c];
            if (srcCh == dstCh)
                continue;

            auto cost = getCost(srcCh, dstCh);
            if (cost < 0)
                return -1;

            result += cost;
        }

        return result;
    }

    Cache m_finalCache;
    Cache m_rules;
    CharCode m_dstCode;
    int m_minCost;
    CharBitset m_visited = {};
    std::array<CharCode, CharCount> m_curSteps;
};
