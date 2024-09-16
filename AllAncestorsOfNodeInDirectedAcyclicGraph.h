#pragma once
#include <algorithm>
#include <bitset>
#include <iterator>
#include <optional>
#include <unordered_set>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> getAncestors(int n, const std::vector<std::vector<int>>& edges) {

        m_visited.reset();

        m_result.resize(n);
        for (const auto& edge : edges)
            m_result[edge[1]].push_back(edge[0]);

        for (auto& res : m_result)
            std::sort(res.begin(), res.end());

        for (size_t i = 0; i < static_cast<size_t>(n); ++i)
            Visit(i);

        m_tmpRes.clear();

        return std::move(m_result);
    }

private:
    void Visit(size_t nodeNum)
    {
        if (m_visited[nodeNum])
            return;
        m_visited[nodeNum] = true;

        auto& parents = m_result[nodeNum];
        if (parents.empty())
            return;

        for (int p : parents)
            Visit(p);

        m_tmpRes = parents;
        for (size_t parentNum = 0; parentNum < parents.size(); ++parentNum)
        {
            const int parent = parents[parentNum];
            auto& src = m_result[parent];
            if (src.empty())
                continue;

            const size_t oldResSize = m_tmpRes.size();
            m_tmpRes.resize(m_tmpRes.size() + src.size());
            memcpy(m_tmpRes.data() + oldResSize, src.data(), src.size() * sizeof(int));
            std::inplace_merge(m_tmpRes.begin(), m_tmpRes.begin() + oldResSize, m_tmpRes.end());
            auto lastUniqueIt = std::unique(m_tmpRes.begin(), m_tmpRes.end());
            m_tmpRes.resize(std::distance(m_tmpRes.begin(), lastUniqueIt));
        }

        std::swap(parents, m_tmpRes);
    }

private:
    std::vector<std::vector<int>> m_result;
    std::bitset<1001> m_visited;
    std::vector<int> m_tmpRes;
};

