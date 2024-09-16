#pragma once
#include <string>

inline int RomanDigitToInt(const char curChar, const char nextChar) {
    switch (curChar) {
    case 'I':
        if (nextChar == 'V' || nextChar == 'X')
            return -1;
        return 1;
    case 'X':
        if (nextChar == 'L' || nextChar == 'C')
            return -10;
        return 10;
    case 'C':
        if (nextChar == 'D' || nextChar == 'M')
            return -100;
        return 100;
    case 'V':
        return 5;
    case 'L':
        return 50;
    case 'D':
        return 500;
    case 'M':
        return 1000;
    }
    return 0;
}

inline int romanToInt(const std::string& s) {

    if (s.empty())
        return 0;

    int result = 0;

    for (size_t i = 1; i < s.size(); ++i)
        result += RomanDigitToInt(s[i-1], s[i]);
    result += RomanDigitToInt(s.back(), '\0');

    return result;
}

inline std::string intToRoman(int num) {
    std::string result;

    if (num >= 1000) {
        const int Ms = num / 1000;
        result += std::string(Ms, 'M');
        num -= Ms * 1000;
    }

    if (num >= 900) {
        result += "CM";
        num -= 900;
    }

    if (num >= 500) {
        result += 'D';
        num -= 500;
    }

    if (num >= 400) {
        result += "CD";
        num -= 400;
    }

    if (num >= 100) {
        const int Cs = num / 100;
        result += std::string(Cs, 'C');
        num -= Cs * 100;
    }

    if (num >= 90) {
        result += "XC";
        num -= 90;
    }

    if (num >= 50) {
        result += 'L';
        num -= 50;
    }

    if (num >= 40) {
        result += "XL";
        num -= 40;
    }

    if (num >= 10) {
        const int Xs = num / 10;
        result += std::string(Xs, 'X');
        num -= Xs * 10;
    }

    if (num == 9) {
        result += "IX";
        num -= 9;
    }


    if (num >= 5) {
        result += 'V';
        num -= 5;
    }

    if (num == 4) {
        result += "IV";
        num -= 4;
    }

    while (num > 0) {
        result += 'I';
        --num;
    }

    return result;
}

