#include "MaximumEarnings.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <map>

#include <intrin.h>

using RoadPoint = uint32_t;
constexpr RoadPoint RoadPointsMax = 100000;

long long MaxTaxiEarningsImpl(const std::vector<std::vector<int>>& rides)
{
    if (rides.empty())
        return 0;

    std::vector<uint16_t> order(rides.size());
    for (uint16_t i = 0; i < static_cast<uint16_t>(rides.size()); ++i)
        order[i] = i;

    std::sort(begin(order), end(order),
        [&](const uint16_t lhsIdx, const uint16_t rhsIdx) {
            const auto& lhs = rides[lhsIdx];
            const auto& rhs = rides[rhsIdx];

            if (lhs[1] < rhs[1])
                return true;
            if (lhs[1] > rhs[1])
                return false;

            if (lhs[0] < rhs[0])
                return true;
            if (lhs[0] > rhs[0])
                return false;

            return lhs[2] > rhs[2]; // ride with equal start and end but higher earn goes first
        });

    auto uniqueEndIt = std::unique(begin(order), end(order),
        [&](const uint16_t lhsIdx, const uint16_t rhsIdx) {
            const auto& lhs = rides[lhsIdx];
            const auto& rhs = rides[rhsIdx];

            return lhs[0] == rhs[0] &&
                lhs[1] == rhs[1];
        });
    order.erase(uniqueEndIt, end(order));
    const size_t rideCount = order.size();

    using RoadPointMaxEarn = std::pair<RoadPoint, long long>;
    auto CmpByRoadPoint = [](const RoadPointMaxEarn& lhs, const RoadPointMaxEarn& rhs) {
        return lhs.first < rhs.first;
    };

    std::vector<RoadPointMaxEarn> maxEarns;
    maxEarns.reserve(rideCount);

    // Put the first element to maxEarn
    {
        const auto& rideInfo = rides[order[0]];
        maxEarns.emplace_back(rideInfo[1], rideInfo[1] - rideInfo[0] + rideInfo[2]);
    }


    for (size_t r = 0; r < rideCount; ++r) {
        const auto& rideInfo = rides[order[r]];
        const int start = rideInfo[0];
        const int end = rideInfo[1];
        const int tip = rideInfo[2];

        long long maxEarnAtStart = 0ll;
        auto maxEarnStartIt = std::upper_bound(maxEarns.begin(), maxEarns.end(), RoadPointMaxEarn{ start, 0ll }, CmpByRoadPoint);
        if (maxEarnStartIt != maxEarns.begin()) {
            --maxEarnStartIt;
            maxEarnAtStart = maxEarnStartIt->second;
        }

        auto earnAtEnd = maxEarnAtStart + end - start + tip;

        auto maxEarnEndIt = std::lower_bound(maxEarnStartIt, maxEarns.end(), RoadPointMaxEarn{ end, 0ll }, CmpByRoadPoint);
        if (maxEarnEndIt != maxEarns.begin())
            earnAtEnd = std::max(earnAtEnd, std::prev(maxEarnEndIt)->second);

        if (maxEarnEndIt == maxEarns.end() || maxEarnEndIt->first != end) {
            maxEarns.emplace_back(end, earnAtEnd);
            maxEarnEndIt = std::prev(maxEarns.end());
            //assert(std::is_sorted(maxEarns.begin(), maxEarns.end(), CmpByRoadPoint));
        }
        else if (maxEarnEndIt->second < earnAtEnd)
            maxEarnEndIt->second = earnAtEnd;

        ++maxEarnEndIt;
        while (maxEarnEndIt != maxEarns.end() && maxEarnEndIt->second < earnAtEnd) {
            maxEarnEndIt->second = earnAtEnd;
            ++maxEarnEndIt;
        }
    }

    return maxEarns.empty() ? 0 : maxEarns.rbegin()->second;
}


std::vector<std::vector<int>> GetRidesData()
{
    std::ifstream ifs("MaximumEarnings_data.txt", std::ios_base::in | std::ios_base::binary | std::ios_base::ate);

    const auto ifsSize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    if (!ifsSize)
        return {};

    std::vector<char> buffer;
    buffer.resize(static_cast<size_t>(ifsSize));
    ifs.read(buffer.data(), buffer.size());


    std::vector<std::vector<int>> result;

    size_t pos = 1;
    std::vector<int> tokens;
    while (pos + 1 < buffer.size()) {
        const char ch = buffer[pos++];

        if (ch == '[') {
            tokens.clear();
            tokens.push_back(0);
        }
        else if (ch == ']') {
            if (!tokens.empty()) {
                result.push_back(std::move(tokens));
                tokens = {};
            }
        }
        else if (ch == ',') {
            tokens.push_back(0);
        }
        else if (ch >= '0' && ch <= '9') {
            const int digit = ch - '0';
            auto& token = tokens.back();
            token = token*10 + digit;
        }
        else if (std::isspace(ch))
            continue;
        else {
            __debugbreak();
        }
    }

    return result;
}
