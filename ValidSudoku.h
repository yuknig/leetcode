#pragma once
#include <vector>

class Solution {
public:
    bool isValidSudoku(const std::vector<std::vector<char>>& board) {

        bool digitExistsInRow[9][10] = { false };
        bool digitExistsInCol[9][10] = { false };
        bool digitExistsInSubBox[3][3][10] = { false };

        for (int y = 0; y < 9; ++y)
        {
            const auto& row = board[y];
            const int subBoxY = y / 3;
            for (int x = 0; x < 9; ++x)
            {
                const int digit = row[x] - '0';
                if (digit < 0 || digit > 9)
                    continue;

                const int subBoxX = x / 3;

                if (std::exchange(digitExistsInRow[y][digit], true))
                    return false;
                if (std::exchange(digitExistsInCol[x][digit], true))
                    return false;

                if (std::exchange(digitExistsInSubBox[subBoxY][subBoxX][digit], true))
                    return false;
            }
        }

        return true;
    }
};
