#pragma once
#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>
#include <optional>


int SignDiff(const int lhs, const int rhs) {
    const int diff = lhs - rhs;
    if (diff < 0)
        return -1;
    if (diff > 0)
        return 1;
    return 0;
}

enum SqType
{
    Inc,
    Dec,
    Flat,
};

struct Interval
{
    ptrdiff_t first;
    ptrdiff_t last;
    SqType type;

    size_t Length() const {
        return last - first + 1;
    }
};

size_t SumInInterval(size_t length)
{
    size_t sum = 0;
    for (size_t i = 1; i <= length; ++i)
        sum += i;
    return sum;
    //return (length / 2) * (1 + length);
}


int CandyImpl(const std::vector<int>& ratings) {
    if (ratings.empty())
        return 0;

    std::vector<Interval> intervals;

    size_t idx = 0;
    while (idx < ratings.size()) {

        const size_t startIdx = idx++;
        const int curR = ratings[startIdx];
        if (idx == ratings.size()) {
            intervals.emplace_back(startIdx, startIdx, SqType::Flat);
            break;
        }

        const int nextR = ratings[idx];
        if (nextR < curR) {
            do {
                ++idx;
            } while (idx < ratings.size() && ratings[idx] < ratings[idx-1]);
            intervals.emplace_back(startIdx, idx - 1, SqType::Dec);
        }
        else if (nextR > curR) {
            do {
                ++idx;
            } while (idx < ratings.size() && ratings[idx] > ratings[idx - 1]);
            intervals.emplace_back(startIdx, idx - 1, SqType::Inc);
        }
        else {
            do {
                ++idx;
            } while (idx < ratings.size() && ratings[idx] == ratings[idx - 1]);
            if (idx - startIdx > 1 && idx != ratings.size())
                --idx;
            intervals.emplace_back(startIdx, idx - 1, SqType::Flat);
        }
    }

    std::vector<uint16_t> candies(ratings.size(), 1);
    auto SetElm = [&](const size_t num, uint16_t value) {
        candies[num] = std::max(candies[num], value);
    };

    for (size_t intervalNum = 0; intervalNum < intervals.size(); ++intervalNum) {
        const auto& interval = intervals[intervalNum];
        switch (interval.type) {
        case SqType::Inc:
        {
            if (interval.first > 0 && ratings[interval.first - 1] < ratings[interval.first]) {
                SetElm(interval.first, candies[interval.first - 1] + 1);
            }

            const auto startValue = candies[interval.first];
            for (size_t i = 0; i < interval.Length(); ++i) {
                const size_t idx = interval.first + i;
                SetElm(idx, static_cast<uint16_t>(startValue + i));
            }
        }
        break;
        case SqType::Dec:
        {
            const auto startValue = candies[interval.last];
            for (size_t i = 0; i < interval.Length(); ++i) {
                const size_t idx = interval.last - i;
                SetElm(idx, static_cast<uint16_t>(startValue + i));
            }
            if (interval.first > 0 && ratings[interval.first - 1] > ratings[interval.first]) {
                SetElm(interval.first - 1, candies[interval.first] + 1);
            }
        }
        break;
        case SqType::Flat:
            for (size_t i = 0; i < interval.Length(); ++i) {
                const size_t idx = interval.first + i;
                SetElm(idx, 1);
            }
            if (interval.first > 0 && ratings[interval.first - 1] < ratings[interval.first])
                SetElm(interval.first, candies[interval.first-1] + 1);
            break;
        }
    }

    int sum = std::accumulate(candies.begin(), candies.end(), 0);
    return sum;

    /*for (size_t i = 0; i < intervals.size(); ++i) {
        const auto& curInterval = intervals[i];

        switch (curInterval.type) {
        case SqType::Inc:
            sum += SumInInterval(curInterval.Length());
            break;
        case SqType::Dec:
            sum += SumInInterval(curInterval.Length());
            break;
        case SqType::Flat:
            sum += curInterval.Length();
            break;
        }

        if (i + 1 < intervals.size()) {
            const auto& nextInterval = intervals[i + 1];
            switch (curInterval.type) {
            case SqType::Inc:
                break;
            case SqType::Dec:
                if (nextInterval.type == SqType::Flat ||
                    nextInterval.type == SqType::Inc) {
                    ++sum;
                }
                break;
            case SqType::Flat:
                break;
            }
        }
    }*/

    //return static_cast<int>(sum);
}
