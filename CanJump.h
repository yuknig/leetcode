#pragma once
#include <vector>

inline bool CanJumpImpl(const std::vector<int>& nums) {
    const int dest = nums.size() - 1;
    std::vector<bool> visited(nums.size(), false);

    std::vector<uint16_t> q;
    q.push_back(0);

    while (!q.empty()) {
        const auto curPos = q.back();
        q.pop_back();
        if (curPos == dest)
            return true;

        const auto jumpFrom = curPos + 1;
        const auto jumpTo = std::min(curPos + nums[curPos], dest);
        for (int i = jumpFrom; i <= jumpTo; ++i) {
            if (!visited[i]) {
                visited[i] = true;
                q.push_back(i);
            }
        }
    }

    return false;
}

inline int JumpSteps(const std::vector<int>& nums) {
    std::vector<int> minSteps(nums.size(), INT_MAX);
    minSteps[0] = 0;

    for (size_t i = 0; i < nums.size() - 1; ++i) {
        const auto curSteps = minSteps[i] + 1;
        const auto jumpLength = nums[i];
        const auto jumpFrom = i + 1;
        const auto jumpTo = std::min(i + jumpLength, nums.size() - 1);
        for (size_t j = jumpFrom; j <= jumpTo; ++j) {
            minSteps[j] = std::min(minSteps[j], curSteps);
        }
    }

    return minSteps.back();
}
