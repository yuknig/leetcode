#pragma once
#include <deque>
#include <vector>

inline int numIslands(std::vector<std::vector<char>>& grid) {
    const uint16_t h = static_cast<uint16_t>(grid.size());
    if (!h)
        return 0;

    const uint16_t w = static_cast<uint16_t>(grid[0].size());
    if (!w)
        return 0;

    int islands = 0;

    std::deque<std::pair<uint16_t, uint16_t>> q;

    for (uint16_t y = 0; y < h; ++y) {
        auto& row = grid[y];
        for (uint16_t x = 0; x < w; ++x) {
            if (row[x] != '1')
                continue;

            ++islands;

            row[x] = 'x';
            q.emplace_back(x, y);


            do {
                const auto [curX, curY] = q.back();
                q.pop_back();

                auto& curRow = grid[curY];

                if (curX > 0 && curRow[curX - 1] == '1') {
                    curRow[curX - 1] = 'x';
                    q.emplace_back(curX - 1, curY);
                }
                if (curX < w - 1 && curRow[curX + 1] == '1') {
                    curRow[curX + 1] = 'x';
                    q.emplace_back(curX + 1, curY);
                }

                if (curY > 0 && grid[curY - 1][curX] == '1') {
                    grid[curY - 1][curX] = 'x';
                    q.emplace_back(curX, curY - 1);
                }
                if (curY < h - 1 && grid[curY + 1][curX] == '1') {
                    grid[curY + 1][curX] = 'x';
                    q.emplace_back(curX, curY + 1);
                }

            } while (!q.empty());
        }
    }

    return islands;
}
