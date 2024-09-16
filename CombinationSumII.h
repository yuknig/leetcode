#pragma once
#include <algorithm>
#include <array>
#include <cassert>
#include <vector>

// https://leetcode.com/problems/combination-sum-ii/

class Solution {
public:
    static constexpr int MaxTarget = 30;
    using Hist = std::array<uint8_t, MaxTarget + 1>;

    std::vector<std::vector<int>> combinationSum2(const std::vector<int>& candidates, int target) {

        m_hist = {};
        for (int c : candidates) {
            if (c <= MaxTarget)
                ++m_hist[c];
        }

        Visit(target, target);

        return m_result;
    }

    void Visit(int targetRemining, int rightBound)
    {
        for (int i = rightBound; i > 0; --i)
        {
            if (!m_hist[i])
                continue;

            if (i > targetRemining)
                continue;

            m_curCombination.push_back(i);
            --m_hist[i];
            if (targetRemining == i)
                m_result.push_back(m_curCombination);
            else if (i > 0)
                Visit(targetRemining - i, i);

            ++m_hist[i];
            assert(m_curCombination.back() == i);
            m_curCombination.pop_back();
        }
    }

private:
    Hist m_hist;
    std::vector<std::vector<int>> m_result;
    std::vector<int> m_curCombination;
};
