#pragma once
#include <array>
#include <cassert>
#include <string>

constexpr uint8_t GetCharCode(char ch)
{
    return ch - 'A';
}

constexpr uint8_t MaxCharCode = GetCharCode('z');
using Hist = std::array<int32_t, MaxCharCode + 1>;

Hist CalcHist(const std::string_view& s)
{
    Hist result = {};
    for (char ch : s)
        ++result[GetCharCode(ch)];
    return result;
}


class Solution
{
public:
    std::string minWindow(const std::string& s, const std::string& t) {

        if (s.size() < t.size())
            return {};

        m_sv = s;
        m_tHist = CalcHist(t);
        m_curHist = m_tHist;
        m_charsLeft = static_cast<uint32_t>(t.size());

        const size_t maxLIdx = s.size() - t.size();
        uint32_t lIdx = 0;
        uint32_t rIdx = 0;

        size_t resultStart = 0;
        size_t resultLength = UINT_MAX;

        while (lIdx <= maxLIdx)
        {
            bool foundSq = false;
            while (rIdx < s.size())
            {
                if (HandleRightChar(rIdx++))
                {
                    foundSq = true;
                    break;
                }
            }

            if (!foundSq)
                break;

            while (lIdx < rIdx && lIdx <= maxLIdx)
            {
                const bool res = HandleLeftChar(lIdx++);
                if (res)
                {
                    const size_t curLen = rIdx - lIdx + 1;
                    if (curLen < resultLength)
                    {
                        resultLength = curLen;
                        resultStart = lIdx - 1;
                    }
                    break;
                }
            }
        }

        return resultLength == UINT_MAX ? "" : s.substr(resultStart, resultLength);
    }

    bool HandleRightChar(uint32_t rIdx)
    {
        const char ch = m_sv[rIdx];
        const uint8_t chCode = GetCharCode(ch);
        if (m_tHist[chCode] > 0)
        {
            if (--m_curHist[chCode] >= 0)
            {
                if (--m_charsLeft == 0)
                    return true;
            }
        }

        return false;
    }

    bool HandleLeftChar(uint32_t lIdx)
    {
        const char ch = m_sv[lIdx];
        const uint8_t chCode = GetCharCode(ch);
        if (m_tHist[chCode] > 0)
        {
            if (++m_curHist[chCode] > 0)
            {
                ++m_charsLeft;
                return true;
            }
        }

        return false;
    }

private:
    std::string_view m_sv;
    Hist m_tHist;
    Hist m_curHist;
    uint32_t m_charsLeft;
};
