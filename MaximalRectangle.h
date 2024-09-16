#pragma once
#include <vector>

inline int MaximalRectangleImpl(const std::vector<std::vector<char>>& matrix) {
    const int h = static_cast<int>(matrix.size());
    if (!h)
        return 0;

    const int w = static_cast<int>(matrix[0].size());
    if (!w)
        return 0;

    std::vector<std::pair<uint8_t, uint8_t>> cellsFilled(w*h);
    for (int y = h - 1; y >= 0; --y) {
        for (int x = w - 1; x >= 0; --x) {
            if (matrix[y][x] == '0')
                continue;

            auto& cell = cellsFilled[y*w+x];
            cell = { 1, 1 };
            if (x < w - 1) {
                const auto& cellNextX = cellsFilled[y*w + x + 1];
                cell.first += cellNextX.first;
            }
            if (y < h - 1) {
                const auto& cellNextY = cellsFilled[(y + 1)*w + x];
                cell.second += cellNextY.second;
            }
        }
    }

    int maxSquare = 0;

    for (int y = 0; y < h; ++y) {
        const int rowOffset = y * w;
        for (int x = 0; x < w; ++x) {
            const int cellOffset = rowOffset + x;
            const auto* pCell = &cellsFilled[cellOffset];
            if (!pCell->first)
                continue;

            const auto [cellW, cellH] = *pCell;

            // Handle 'vertical' rectangles with left top corner at (x, y)
            {
                int minH = cellH;
                for (uint8_t cx = 0; cx < cellW; ++cx) {
                    const int curH = (pCell + cx)->second;
                    minH = std::min(minH, curH);

                    const int curSquare = (cx + 1) * minH;
                    maxSquare = std::max(maxSquare, curSquare);
                }
            }

            // Handle 'horizontal' rectangles with left top corner at (x, y)
            {
                int minW = cellW;
                for (uint8_t cy = 0; cy < cellH; ++cy) {
                    const int curW = (pCell + w*cy)->first;
                    minW = std::min(minW, curW);

                    const int curSquare = (cy + 1) * minW;
                    maxSquare = std::max(maxSquare, curSquare);
                }
            }
        }
    }

    return maxSquare;
}
