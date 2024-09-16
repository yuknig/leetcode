#pragma once
#include <cassert>
#include <vector>

// https://leetcode.com/problems/count-sub-islands/

class Solution {
public:
    int countSubIslands(std::vector<std::vector<int>>& grid1, std::vector<std::vector<int>>& grid2) {
        m_grid1 = &grid1;
        m_grid2 = &grid2;
        m_height = grid1.size();
        m_width = grid1[0].size();

        int count = 0;
        for (size_t y = 0; y < m_height; ++y)
        {
            for (size_t x = 0; x < m_width; ++x)
            {
                if (grid2[y][x] == 1 && Visit(x, y))
                    ++count;
            }
        }

        return count;
    }

    bool Visit(size_t x, size_t y)
    {
        auto& curRow = (*m_grid2)[y];
        /*if (curRow[x] != 1)
            return true;*/

        curRow[x] = 2;

        bool result = (*m_grid1)[y][x] == 1;
        if (x > 0 && curRow[x-1] == 1)
            result = Visit(x-1, y) && result;
        if (x + 1 < m_width && curRow[x+1] == 1)
            result = Visit(x+1, y) && result;

        if (y > 0 && (*m_grid2)[y-1][x] == 1)
            result = Visit(x, y - 1) && result;
        if (y + 1 < m_height && (*m_grid2)[y+1][x] == 1)
            result = Visit(x, y + 1) && result;

        return result;
    }

private:
    std::vector<std::vector<int>>* m_grid1;
    std::vector<std::vector<int>>* m_grid2;
    size_t m_width;
    size_t m_height;
};
