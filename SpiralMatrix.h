#pragma once
#include <vector>

// https://leetcode.com/problems/spiral-matrix

class Solution {
public:
    std::vector<int> spiralOrder(const std::vector<std::vector<int>>& matrix) {

        const int height = static_cast<int>(matrix.size());
        const int width  = static_cast<int>(matrix[0].size());

        int x1 = 0;
        int y1 = 0;
        int x2 = width - 1;
        int y2 = height - 1;
        std::vector<int> result;
        result.reserve(width * height);

        while (x1 <= x2 && y1 <= y2)
        {
            const auto& firstRow = matrix[y1];
            for (int x = x1; x <= x2; ++x)
                result.push_back(firstRow[x]);

            for (int y = y1 + 1; y <= y2; ++y)
                result.push_back(matrix[y][x2]);

            if (y2 > y1)
            {
                const auto& lastRow = matrix[y2];
                for (int x = x2 - 1; x >= x1; --x)
                    result.push_back(lastRow[x]);
            }

            if (x2 > x1)
            {
                for (int y = y2 - 1; y > y1; --y)
                    result.push_back(matrix[y][x1]);
            }

            ++x1;
            --x2;
            ++y1;
            --y2;
        }

        return result;
    }
};
