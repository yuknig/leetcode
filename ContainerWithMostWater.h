#pragma once
#include <algorithm>
#include <vector>

constexpr size_t MaxHeight = 10'000;

inline int maxArea(const std::vector<int>& height) {
    std::pair<uint32_t, uint32_t> borderAtHeight[MaxHeight];
    int maxY = 0;

    {
        for (int x = 0; x < static_cast<int>(height.size()); ++x) {
            const int y = height[x];
            if (y > maxY) {
                for (int i = maxY; i <= y; ++i)
                    borderAtHeight[i].first = x;
                maxY = y;
            }
        }

        maxY = 0;
        for (int x = static_cast<int>(height.size()) - 1; x >= 0; --x) {
            const int y = height[x];
            if (y > maxY) {
                for (int i = maxY; i <= y; ++i)
                    borderAtHeight[i].second = x;
                maxY = y;
            }
        }
    }

    int maxArea = 0;

    int lastLeftX = -1;
    int lastRightX = -1;

    for (int y = maxY; y >= 0; --y) {
        const auto [curLeftX, curRightX] = borderAtHeight[y];
        if (curLeftX != lastLeftX || curRightX != lastRightX) {
            const int yLeft = height[curLeftX];
            const int yRight = height[curRightX];
            const int curArea = std::min(yLeft, yRight) * (curRightX - curLeftX);
            maxArea = std::max(maxArea, curArea);

            lastLeftX = curLeftX;
            lastRightX = curRightX;
        }
    }

    return maxArea;
}
