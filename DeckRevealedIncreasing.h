#pragma once
#include <algorithm>
#include <deque>
#include <numeric>
#include <vector>

std::vector<uint16_t> GetOrder(uint16_t count) {
    std::deque<uint16_t> src(count);
    std::iota(src.begin(), src.end(), 0);

    std::vector<uint16_t> dst;
    dst.reserve(count);

    while (!src.empty()) {
        dst.push_back(src.front());
        src.pop_front();

        if (src.empty())
            break;

        auto second = src.front();
        src.pop_front();
        src.push_back(second);
    }

    std::vector<uint16_t> order;
    order.reserve(count);
    for (uint16_t i = 0; i < count; ++i) {
        auto findI = std::find(dst.begin(), dst.end(), i);
        order.push_back(static_cast<uint16_t>(std::distance(dst.begin(), findI)));
    }

    return order;
}

inline std::vector<int> deckRevealedIncreasing(std::vector<int>& deck) {

    std::sort(deck.begin(), deck.end());

    const auto order = GetOrder(static_cast<uint16_t>(deck.size()));

    std::vector<int> newDeck;
    newDeck.reserve(deck.size());
    for (uint16_t pos : order)
        newDeck.push_back(deck[pos]);

    return newDeck;
}
