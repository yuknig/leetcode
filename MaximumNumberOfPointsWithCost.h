#pragma once
#include <cassert>
#include <deque>
#include <numeric>
#include <vector>

// https://leetcode.com/problems/maximum-number-of-points-with-cost

//
//class Solution {
//public:
//    long long maxPoints(std::vector<std::vector<int>>& points) {
//
//        m_values = &points;
//
//        m_height = static_cast<int>(points.size());
//        const auto& valuesFirstRow = points[0];
//        m_width  = static_cast<int>(points[0].size());
//
//        m_maxMap.resize(m_width * m_height, -1);
//
//        std::vector<int> order(m_width);
//        std::iota(order.begin(), order.end(), 0);
//        std::sort(order.begin(), order.end(),
//            [&](int lhs, int rhs) {
//                return valuesFirstRow[lhs] > valuesFirstRow[rhs];
//        });
//
//        for (int i = 0; i < m_width; ++i)
//        {
//            const int x = order[i];
//            Visit(x, 0, valuesFirstRow[x]);
//        }
//
//        size_t maxMapOffset = (m_height - 1) * m_width;
//        long long maxValue = m_maxMap[maxMapOffset];
//        for (int x = 1; x < m_width; ++x)
//        {
//            maxValue = std::max(maxValue, m_maxMap[maxMapOffset + x]);
//        }
//
//        return maxValue;
//    }
//
//private:
//    void Visit(const int x, const int y, const long long newMaxValue)
//    {
//        long long& maxMapAtPoint = m_maxMap[y*m_width + x];
//        if (newMaxValue <= maxMapAtPoint)
//            return;
//
//        maxMapAtPoint = newMaxValue;
//
//        if (y + 1 == m_height)
//            return;
//
//        const auto left  = std::max(0ll, x - newMaxValue);
//        const auto right = std::min(m_width - 1ll, x + newMaxValue);
//
//        auto& valuesNextRow = (*m_values)[y + 1];
//        const size_t nextRowOffset = m_width * (y + 1);
//
//        for (auto c = x; c >= left; --c)
//        {
//            auto& nextRowMaxElm = m_maxMap[nextRowOffset + c];
//            const auto nextRowValueThere = newMaxValue - (x - c);
//            const auto nextRowMaxValue = nextRowValueThere + valuesNextRow[c];
//            if (nextRowMaxValue > nextRowMaxElm)
//                Visit(c, y + 1, nextRowMaxValue);
//            else
//                break;
//        }
//
//        for (auto c = x + 1; c <= right; ++c)
//        {
//            auto& nextRowMaxElm = m_maxMap[nextRowOffset + c];
//            const auto nextRowValueThere = newMaxValue - (c - x);
//            const auto nextRowMaxValue = nextRowValueThere + valuesNextRow[c];
//            if (nextRowMaxValue > nextRowMaxElm)
//                Visit(c, y + 1, nextRowMaxValue);
//            else
//                break;
//        }
//    }
//
//    const std::vector<std::vector<int>>* m_values;
//    std::vector<long long> m_maxMap;
//    int m_width;
//    int m_height;
//};

class Solution {
public:
    long long maxPoints(std::vector<std::vector<int>>& points) {
        const int height = static_cast<int>(points.size());
        if (!height)
            return 0;

        const auto& valuesFirstRow = points[0];
        const int width = static_cast<int>(valuesFirstRow.size());

        std::vector<long long> sum(width * 2, 0);
        auto* sumSrc = sum.data();
        auto* sumDst = sumSrc + width;

        std::copy(valuesFirstRow.begin(), valuesFirstRow.end(), sumDst);

        for (int r = 1; r < height; ++r)
        {
            std::swap(sumSrc, sumDst);
            
            memset(sumDst, 0, width * sizeof(long long));

            FillDistArray(sumDst, sumSrc, width);
            SumArray(sumDst, points[r]);
        }

        auto maxIt = std::max_element(sumDst, sumDst+width);
        return *maxIt;
    }

    static void FillDistArray(long long* const rowDst, const long long* const rowSrc, const int width)
    {
        auto curPoints = rowSrc[0];
        for (int x = 0; x < width; ++x, --curPoints)
        {
            const auto curSrcValue = rowSrc[x];
            if (curSrcValue > curPoints)
            {
                curPoints = curSrcValue;
                for (int rx = 1; rx <= x; ++rx)
                {
                    const auto curPointsLeft = curSrcValue - rx;
                    if (curPointsLeft <= 0)
                        break;

                    const int cx = x - rx;
                    if (rowDst[cx] < curPointsLeft)
                        rowDst[cx] = curPointsLeft;
                }
            }

            rowDst[x] = curPoints;
        }
    }

    static void SumArray(long long* const lhs, const std::vector<int>& rhs)
    {
        const int width = static_cast<int>(rhs.size());
        for (int x = 0; x < width; ++x)
            lhs[x] += rhs[x];
    }
};

