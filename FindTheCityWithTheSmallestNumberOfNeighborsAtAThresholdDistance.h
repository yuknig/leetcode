#pragma once
#include <algorithm>
#include <vector>

//https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/

class Solution {
public:

    using CityId = uint8_t;

    struct Connection
    {
        CityId m_city;
        int weight;
    };

    struct City
    {
        std::vector<Connection> m_connections;
        int m_neighbourCount = 0;
    };

    void FindConnectionCount(int& neighbourCount, const CityId cityId, const int curDistance)
    {
        if (curDistance >= m_distances[cityId])
            return;

        const int oldDistance = std::exchange(m_distances[cityId], curDistance);
        if (curDistance > 0 && oldDistance == UINT16_MAX)
            ++neighbourCount;

        const auto& city = m_cities[cityId];
        for (const auto& con : city.m_connections)
        {
            if (curDistance + con.weight <= m_maxDistance)
                FindConnectionCount(neighbourCount, con.m_city, curDistance + con.weight);
        }
    }

    inline int findTheCity(int n, const std::vector<std::vector<int>>& edges, int distanceThreshold) {
        m_cities.resize(n);
        m_distances.resize(n);
        m_maxDistance = distanceThreshold;

        for (const auto& edge : edges)
        {
            const CityId city1 = static_cast<CityId>(edge[0]);
            const CityId city2 = static_cast<CityId>(edge[1]);
            const int weight = edge[2];

            m_cities[city1].m_connections.emplace_back(city2, weight);
            m_cities[city2].m_connections.emplace_back(city1, weight);
        }

        int minNeightbouts = INT_MAX;
        for (CityId c = 0; c < static_cast<CityId>(n); ++c)
        {
            std::fill(m_distances.begin(), m_distances.end(), UINT16_MAX);

            auto& neighboursCount = m_cities[c].m_neighbourCount;
            FindConnectionCount(neighboursCount, c, 0);
            if (neighboursCount <= m_cities[m_fewestNeighboursCityId].m_neighbourCount)
                m_fewestNeighboursCityId = c;
        }

        return m_fewestNeighboursCityId;
    }

private:
    std::vector<City> m_cities;
    std::vector<uint16_t> m_distances;
    int m_maxDistance;
    int m_fewestNeighboursCityId = 0;
};
