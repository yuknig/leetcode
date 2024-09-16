#pragma once
#include <vector>

using CityId = int8_t;
using Price = uint32_t;


int FindCheapestPriceImpl(const std::vector<std::vector<int>>& _flights, CityId _src, CityId _dst, int _maxStops);

const std::vector<std::vector<int>>& GetCheapestFlightBigData();
