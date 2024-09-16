#pragma once
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <vector>

// https://leetcode.com/problems/walking-robot-simulation


class Solution {
public:
    int robotSim(const std::vector<int>& commands, const std::vector<std::vector<int>>& obstacles) {

        for (const auto& obstVec : obstacles) {
            const int16_t x = static_cast<int16_t>(obstVec[0]);
            const int16_t y = static_cast<int16_t>(obstVec[1]);

            m_obstaclesX[x].push_back(y);
            m_obstaclesY[y].push_back(x);
        };

        for (auto& [_, vec] : m_obstaclesX)
            std::sort(vec.begin(), vec.end());
        for (auto& [_, vec] : m_obstaclesY)
            std::sort(vec.begin(), vec.end());

        int maxDistSqr = 0;

        for (const int command : commands)
        {
            switch (command)
            {
            case -2:
                if (++m_dir > 3)
                    m_dir = 0;
                break;
            case -1:
                if (--m_dir < 0)
                    m_dir = 3;
                break;
            case 0:
                continue;
                break;
            default:
            {
                switch (m_dir)
                {
                case 0:
                    IncXPos(command);
                    break;
                case 1:
                    IncYPos(command);
                    break;
                case 2:
                    DecXPos(command);
                    break;
                case 3:
                    DecYPos(command);
                    break;
                }
                const int distSqr = m_posX*m_posX + m_posY*m_posY;
                if (distSqr > maxDistSqr)
                    maxDistSqr = distSqr;
            }
            }
        }

        return maxDistSqr;
    }

private:
    void IncXPos(uint16_t delta)
    {
        auto findYIt = m_obstaclesY.find(m_posY);
        if (findYIt != m_obstaclesY.end())
        {
            const auto& vec = findYIt->second;
            auto findXIt = std::lower_bound(vec.begin(), vec.end(), m_posX+1);
            if (findXIt != vec.end())
            {
                m_posX = std::min(m_posX + delta, *findXIt - 1);
                return;
            }
        }

        m_posX += delta;
    }

    void DecXPos(uint16_t delta)
    {
        auto findYIt = m_obstaclesY.find(m_posY);
        if (findYIt != m_obstaclesY.end())
        {
            const auto& vec = findYIt->second;
            auto findXIt = std::lower_bound(vec.begin(), vec.end(), m_posX);
            if (findXIt != vec.begin())
            {
                --findXIt;
                m_posX = std::max(m_posX - delta, *findXIt + 1);
                return;
            }
        }

        m_posX -= delta;
    }

    void IncYPos(uint16_t delta)
    {
        auto findXIt = m_obstaclesX.find(m_posX);
        if (findXIt != m_obstaclesX.end())
        {
            const auto& vec = findXIt->second;
            auto findYIt = std::lower_bound(vec.begin(), vec.end(), m_posY+1);
            if (findYIt != vec.end())
            {
                m_posY = std::min(m_posY + delta, *findYIt - 1);
                return;
            }
        }

        m_posY += delta;
    }

    void DecYPos(uint16_t delta)
    {
        auto findXIt = m_obstaclesX.find(m_posX);
        if (findXIt != m_obstaclesX.end())
        {
            const auto& vec = findXIt->second;
            auto findYIt = std::lower_bound(vec.begin(), vec.end(), m_posY);
            if (findYIt != vec.begin())
            {
                --findYIt;
                m_posY = std::max(m_posY - delta, *findYIt + 1);
                return;
            }
        }

        m_posY -= delta;
    }

private:
    // Direction (m_dir) values
    //       1
    //      / \
    // 2 <-- |--> 0
    //      \ /
    //       3
    int8_t m_dir = 1;
    int16_t m_posX = 0;
    int16_t m_posY = 0;

    std::unordered_map<int16_t, std::vector<int16_t>> m_obstaclesX;
    std::unordered_map<int16_t, std::vector<int16_t>> m_obstaclesY;
};
