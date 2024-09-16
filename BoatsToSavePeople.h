#pragma once
#include <algorithm>
#include <map>
#include <set>
#include <vector>

inline int numRescueBoats(std::vector<int> people, int limit) {

    if (people.empty())
        return 0;

    std::sort(people.begin(), people.end());

    const int minWeight = people.front();
    int heavyPeople = 0; // too heavy to have companion
    for (int i = static_cast<int>(people.size()) - 1; i >= 0; --i) {
        if (people[i] + minWeight > limit)
            ++heavyPeople;
        else
            break;
    }

    people.resize(people.size() - heavyPeople);

    std::vector<bool> used;

    int numBoats = 0;
    for (int i = static_cast<int>(people.size()) - 1; i >= 0; --i) {
        if (i < used.size() && used[i])
            continue;

        if (i == 0) {
            ++numBoats;
            break;
        }

        const int restWeight = limit - people[i];
        auto endCompanion = people.begin() + i;
        auto findIt = std::upper_bound(people.begin(), endCompanion, restWeight);
        if (findIt != people.begin())
            --findIt;

        auto findIdx = std::distance(people.begin(), findIt);
        bool found = false;
        for (ptrdiff_t j = findIdx; j >= 0; --j) {
            if (static_cast<size_t>(j) < used.size() && used[j])
                continue;

            if (people[j] > restWeight)
                continue;

            if (static_cast<size_t>(j) >= used.size())
                used.resize(j + 1);
            used[j] = true;
            found = true;
            break;
        }

        ++numBoats;
    }

    return numBoats + heavyPeople;
}