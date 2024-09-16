#pragma once
#include <array>

// https://leetcode.com/problems/happy-number

class Solution {
public:
    bool isHappy(const int number) {
        constexpr int MaxIterations = 16;

        int num = number;
        std::array<uint8_t, 10> digits;
        for (int i = 0; i < MaxIterations; ++i)
        {
            const auto digitCount = SplitDigits(num, digits);

            int sum = 0;
            for (int digitNum = 0; digitNum < digitCount; ++digitNum)
            {
                const auto digit = digits[digitNum];
                sum += digit * digit;
            }

            if (sum == 1)
                return true;

            if (sum == number)
                return false;

            if (sum >= 1 << 30)
                return false;

            num = sum;
        }

        return false;
    }

private:
    static uint8_t SplitDigits(int n, std::array<uint8_t, 10>& dst)
    {
        for(int digitNum = 0; digitNum < 10; ++digitNum)
        {
            const uint8_t digit = n % 10;
            dst[digitNum] = digit;
            n /= 10;
            if (!n)
                return digitNum + 1;
        }

        return 10;
    }

};
