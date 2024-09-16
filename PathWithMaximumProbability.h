#pragma once
#include <vector>
#include <map>
#include <unordered_map>

// https://leetcode.com/problems/path-with-maximum-probability/

class Solution {
public:
    using VertexId = uint16_t;
    using Probability = double;

    static constexpr size_t MaxVertexCount = 10'000;

    double maxProbability(int n, const std::vector<std::vector<int>>& edges, const std::vector<double>& succProb, int start_node, int end_node) {

        for (size_t i = 0; i < edges.size(); ++i)
        {
            const auto& edge = edges[i];
            const auto v1Id = static_cast<VertexId>(edge[0]);
            const auto v2Id = static_cast<VertexId>(edge[1]);
            const auto prob = static_cast<Probability>(succProb[i]);

            auto& v1 = m_vertices[v1Id];
            v1.m_connections.emplace_back(v2Id, prob);

            auto& v2 = m_vertices[v2Id];
            v2.m_connections.emplace_back(v1Id, prob);
        }

        //for (auto& entry : m_vertices)
        //{
        //    auto& connections = entry.m_connections;
        //    std::sort(connections.begin(), connections.end(),
        //        [](const Connection& lhs, const Connection& rhs) {
        //            return lhs.m_prob > rhs.m_prob;
        //        });
        //}

        m_end = static_cast<VertexId>(end_node);
        Visit(m_vertices[start_node], start_node, 1);

        return m_bestProb;
    }

private:
    struct Connection
    {
        VertexId m_id;
        Probability m_prob = 0;
    };

    struct Vertex
    {
        std::vector<Connection> m_connections;
        Probability m_maxProb = 0;
        bool m_visited = false;
    };

    void Visit(Vertex& vertex, const VertexId vertexId, const Probability vertexProb)
    {
        assert(vertex.m_maxProb < vertexProb);
        assert(!vertex.m_visited);

        vertex.m_maxProb = vertexProb;
        if (vertexId == m_end)
        {
            m_bestProb = std::max(m_bestProb, vertexProb);
            return;
        }

        vertex.m_visited = true;

        for (const Connection& c : vertex.m_connections)
        {
            auto& curVertex = m_vertices[c.m_id];
            if (curVertex.m_visited)
                continue;

            const auto newProb = c.m_prob * vertexProb;
            if (newProb < m_bestProb)
                continue;

            if (newProb > curVertex.m_maxProb)
                Visit(curVertex, c.m_id, newProb);
        }

        vertex.m_visited = false;
    }

    std::array<Vertex, MaxVertexCount> m_vertices;
    Probability m_bestProb = 1e-5;
    VertexId m_end;
};
