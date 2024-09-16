#include "TimeToBuyStocks.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <map>
#include <vector>

using Price = int32_t;
using Day = uint32_t;

int MaxProfitImpl1(const std::vector<int>& _prices)
{
    if (_prices.empty())
        return 0;

    std::vector<Price> maxPrices(_prices.size());
    Price maxp = _prices.back();
    for (Day d = static_cast<Day>(_prices.size()); d > 0; --d) {
        maxp = std::max(maxp, _prices[d - 1]);
        maxPrices[d-1] = maxp;
    }

    Price minp = _prices.front();
    Price maxDiff = 0;
    for (Day d = 0; d < static_cast<Day>(maxPrices.size() - 1); ++d) {
        minp = std::min(minp, _prices[d]);
        const Price maxp = maxPrices[d+1];
        const Price diff = maxp - minp;
        maxDiff = std::max(maxDiff, diff);
    }

    return maxDiff;
}

//int MaxProfitImpl(const std::vector<int>& _prices)
//{
//    const Day DayCount = static_cast<Day>(_prices.size());
//    if (!DayCount)
//        return 0;
//
//    using PriceDayPair = std::pair<Price, Day>;
//    std::vector<PriceDayPair> pricesOnDay;
//    pricesOnDay.reserve(_prices.size());
//
//    for (Day d = 0; d < DayCount; ++d) {
//        pricesOnDay.emplace_back(_prices[d], d);
//    }
//    std::sort(pricesOnDay.begin(), pricesOnDay.end());
//
//    const Price MaxPrice = pricesOnDay.back().first;
//    std::vector<Price> maxPrices(DayCount, 0);
//
//    bool changed;
//
//    do {
//        changed = false;
//
//        for (Day d = 0; d < DayCount - 1; ++d) {
//            const Price CurDayPrice = _prices[d];
//            if (CurDayPrice == MaxPrice)
//                continue; // Does not make sense to buy at top price
//
//            const Price MaxPriceOnDay = maxPrices[d];
//            auto higherPriceDayIt = std::lower_bound(pricesOnDay.begin(), pricesOnDay.end(), PriceDayPair{ CurDayPrice, 0 },
//                [](const PriceDayPair& lhs, const PriceDayPair& rhs) {
//                    return lhs.first < rhs.first;
//                });
//
//            auto daysToSellIt = std::prev(pricesOnDay.end());
//            while (daysToSellIt != higherPriceDayIt)
//
//            while (daysToSellIt != pricesOnDay.end()) {
//                const Day dayToCell = daysToSellIt->second;
//                if (dayToCell > d) {
//                    Price price = daysToSellIt->first - CurDayPrice; // TODO: put MaxPriceOnDay - CurDayPrice to variable
//                    assert(price > 0);
//                    price += MaxPriceOnDay;
//                    if (price > maxPrices[dayToCell]) {
//                        maxPrices[dayToCell] = price;
//                        changed = true;
//                    }
//                }
//                ++daysToSellIt;
//            }
//        }
//    }
//    while (changed);
//
//    return *std::max_element(maxPrices.begin(), maxPrices.end());
//}

int MaxProfitImpl(const std::vector<int>& _prices)
{
    const Day DayCount = static_cast<Day>(_prices.size());
    if (!DayCount)
        return 0;

    std::vector<Price> maxPrices(DayCount);
    for (Day buyDay = 0; buyDay < DayCount - 1; ++buyDay) {
        const Price BuyPrice = _prices[buyDay];
        Price maxPrice = maxPrices[buyDay];
        const int priceDiff = maxPrice - BuyPrice;

        Price maxSellPrice = BuyPrice;
        for (Day sellDay = buyDay + 1; sellDay < DayCount; ++sellDay) {
            const Price sellPrice = _prices[sellDay];
            if (sellPrice > maxSellPrice) {
                maxSellPrice = sellPrice;
                maxPrice = priceDiff + maxSellPrice;
            }
            maxPrices[sellDay] = std::max(maxPrices[sellDay], maxPrice);
        }
    }
    return maxPrices.back();
}


std::vector<int> GetMaxStockProfitData()
{
    std::ifstream ifs("MaxStockProfit_data.txt", std::ios_base::in | std::ios_base::binary | std::ios_base::ate);

    const auto ifsSize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    if (!ifsSize)
        return {};

    std::vector<char> buffer;
    buffer.resize(static_cast<size_t>(ifsSize));
    ifs.read(buffer.data(), buffer.size());


    std::vector<int> result(1);

    size_t pos = 1;
    while (pos + 1 < buffer.size()) {
        const char ch = buffer[pos++];

        if (ch == ',') {
            result.push_back(0);
        }
        else if (ch >= '0' && ch <= '9') {
            const int digit = ch - '0';
            auto& n = result.back();
            n = n * 10 + digit;
        }
        else if (std::isspace(ch))
            continue;
        else {
            __debugbreak();
        }
    }

    return result;
}

