#pragma once
#include <algorithm>
#include <bitset>
#include <vector>

// https://leetcode.com/problems/longest-consecutive-sequence

class Solution {
public:
    int longestConsecutive(const std::vector<int>& nums) {
        if (nums.empty())
            return 0;

        auto [minIt, maxIt] = std::minmax_element(nums.begin(), nums.end());
        const int minV = *minIt;
        const int maxV = *maxIt;

        constexpr size_t SpanWidth = 1 << 16;
        std::bitset<SpanWidth> bs;

        std::vector<std::pair<int, int>> sequences;

        int maxLength = 1;
        int spanBegin = minV;
        while (spanBegin <= maxV)
        {
            const int spanEnd = spanBegin + SpanWidth - 1;

            bs.reset();

            for (int n : nums)
            {
                const int offset = n - spanBegin;
                if (offset >= 0 && offset < SpanWidth)
                    bs.set(offset);
            }

            if (bs.any())
            {
                int sqBegin = 0;
                while (sqBegin < SpanWidth)
                {
                    while (sqBegin < SpanWidth && !bs.test(sqBegin))
                        ++sqBegin;

                    int sqEnd = sqBegin + 1;
                    while (sqEnd < SpanWidth && bs.test(sqEnd))
                        ++sqEnd;
                    const int sqLen = sqEnd - sqBegin;

                    if (sqLen > 1)
                    {
                        maxLength = std::max(maxLength, sqLen);
                        if (sqBegin == 0 || sqEnd == SpanWidth)
                            sequences.emplace_back(spanBegin + sqBegin, spanBegin + sqEnd - 1);
                    }

                    sqBegin = sqEnd;
                }
            }

            spanBegin += SpanWidth;
        }

        if (sequences.size() > 1)
        {
            for (size_t sqNum = sequences.size() - 1; sqNum > 0; --sqNum)
            {
                auto& curSq = sequences[sqNum];
                auto& prevSq = sequences[sqNum - 1];
                if (curSq.first == prevSq.second + 1)
                {
                    prevSq.second = curSq.second;
                    maxLength = std::max(maxLength, prevSq.second - prevSq.first + 1);
                }
            }
        }

        return maxLength;
    }
};
