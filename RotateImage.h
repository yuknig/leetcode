#pragma once
#include <vector>

// https://leetcode.com/problems/rotate-image

class Solution {
public:
    void rotate(std::vector<std::vector<int>>& matrix) {
        const int size = static_cast<int>(matrix.size());
        const int halfSize = size / 2;

        for (int r = 0; r < halfSize; ++r)
        {
            const int length = size - r*2;

            for (int l = 0; l < length - 1; ++l)
            {
                const int c1 = r + l;
                const int c2 = r;

                const int x1 = c1;
                const int y1 = c2;

                const int x2 = size - 1 - c2;
                const int y2 = c1;

                const int x3 = size - 1 - c1;
                const int y3 = size - 1 - c2;

                const int x4 = c2;
                const int y4 = size - 1 - x1;

                auto& p1 = matrix[y1][x1];
                auto& p2 = matrix[y2][x2];
                auto& p3 = matrix[y3][x3];
                auto& p4 = matrix[y4][x4];

                const int tmp = std::exchange(p4, p3);
                p3 = p2;
                p2 = p1;
                p1 = tmp;
            }
        }
    }
};
