#pragma once
#include <deque>
#include <vector>
#include <unordered_map>
#include <unordered_set>

inline bool validPath(int n, const std::vector<std::vector<int>>& edges, int source, int destination) {
    if (source == destination)
        return true;

    std::unordered_set<int> visited;
    std::unordered_map<int, std::vector<int>> connections;


    for (const auto& edge : edges) {
        connections[edge[0]].push_back(edge[1]);
        connections[edge[1]].push_back(edge[0]);
    }

    std::deque<int> q;
    q.push_back(destination);
    visited.emplace(destination);

    bool found = false;
    while (!q.empty() && !found) {
        const auto qItem = q.back();
        q.pop_back();

        const auto& vertexConnections = connections[qItem];
        for (int vc : vertexConnections) {
            if (visited.count(vc))
                continue;

            if (vc == source) {
                found = true;
                break;
            }

            q.push_back(vc);
            visited.emplace(vc);
        }
    }

    return found;
}
