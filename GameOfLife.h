#pragma once
#include <vector>
#include <intrin.h>


// https://leetcode.com/problems/game-of-life

class Solution {
public:
    void gameOfLife(std::vector<std::vector<int>>& board) {
        const size_t height = board.size();
        const size_t width = board[0].size();

        std::vector<uint8_t> nc(width * height, 0);
        for (size_t y = 0; y < height; ++y)
        {
            const auto& srcRow = board[y];
            size_t dstOffset = y * width;
            for (size_t x = 0; x < width; ++x, ++dstOffset)
            {
                if (!srcRow[x])
                    continue;

                if (y > 0)
                {
                    const size_t prevRowOffset = dstOffset - width;
                    if (x > 0)
                        ++nc[prevRowOffset - 1];
                    ++nc[prevRowOffset];
                    if (x + 1 < width)
                        ++nc[prevRowOffset + 1];
                }

                if (x > 0)
                    ++nc[dstOffset - 1];
                if (x + 1 < width)
                    ++nc[dstOffset + 1];

                if (y + 1 < height)
                {
                    const size_t nextRowOffset = dstOffset + width;
                    if (x > 0)
                        ++nc[nextRowOffset - 1];
                    ++nc[nextRowOffset];
                    if (x + 1 < width)
                        ++nc[nextRowOffset + 1];
                }
            }
        }

        for (size_t y = 0; y < height; ++y)
        {
            auto& dstRow = board[y];
            size_t srcOffset = y * width;
            for (size_t x = 0; x < width; ++x, ++srcOffset)
            {
                const auto n = nc[srcOffset];
                switch (dstRow[x])
                {
                case 0:
                    if (n == 3)
                        dstRow[x] = 1;
                    break;
                case 1:
                    if (n < 2 || n > 3)
                        dstRow[x] = 0;
                    break;
                }
            }
        }
    }
};
