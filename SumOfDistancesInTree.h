#pragma once
#include <array>
#include <vector>
#include <unordered_map>

constexpr size_t MaxVertexCount = 10'000;

using VertexId = uint16_t;
std::array<std::vector<VertexId>, MaxVertexCount> connections;
int sum;

void Visit(VertexId curVertexNum, VertexId prevVertexNum, int curDist)
{
    sum += curDist;

    const auto& connectedVertices = connections[curVertexNum];
    for (const VertexId v : connectedVertices) {
        if (v == prevVertexNum)
            continue;

        Visit(v, curVertexNum, curDist + 1);
    }
}

inline std::vector<int> sumOfDistancesInTree(int n, const std::vector<std::vector<int>>& edges) {

    for (auto& c : connections)
        c.clear();

    for (const auto& edge : edges) {
        int v1 = edge[0];
        int v2 = edge[1];
        connections[v1].push_back(static_cast<VertexId>(v2));
        connections[v2].push_back(static_cast<VertexId>(v1));
    }

    std::vector<int> result(n);
    for (int vertexNum = 0; vertexNum < n; ++vertexNum) {
        sum = 0;
        Visit(vertexNum, -1, 0);
        result[vertexNum] = sum;
    }

    return result;
}
