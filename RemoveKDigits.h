#pragma once
#include <array>
#include <string>
#include <vector>

std::string minValue;
std::string* pValue;
char minDigitChar;
char maxDigitChar;


void Walk(const std::string_view& sv, const int charsLeft) {
    if (charsLeft <= 0) {
        if (*pValue < minValue)
            minValue = *pValue;
        return;
    }

    const size_t valueChIdx = pValue->size() - charsLeft;
    const char oldValueCh = (*pValue)[valueChIdx];

    for (char d = minDigitChar; d <= maxDigitChar; ++d) {
        if (d > (*pValue)[valueChIdx])
            return;

        int digitPos = -1;
        for (int c = 0; c <= sv.size() - charsLeft; ++c) {
            if (sv[c] == d) {
                digitPos = c;
                break;
            }
        }
        if (digitPos == -1)
            continue;

        (*pValue)[valueChIdx] = d;
        Walk(sv.substr(digitPos + 1), charsLeft - 1);
    }

    (*pValue)[valueChIdx] = oldValueCh;
}

inline std::string removeKdigits(const std::string& num, int k) {

    minDigitChar = '9';
    for (char ch : num) {
        if (ch < minDigitChar) {
            minDigitChar = ch;
            if (ch == 0)
                break;
        }
    }

    maxDigitChar = 0;
    for (char ch : num) {
        if (ch > maxDigitChar) {
            maxDigitChar = ch;
            if (ch == 9)
                break;
        }
    }

    const size_t charCount = num.size() - k;
    const std::string initValue(charCount, '9');
    minValue = initValue;
    std::string curValue = minValue;
    pValue = &curValue;

    Walk(num, static_cast<int>(charCount));

    size_t leadingZeros = minValue.find_first_not_of('0');
    if (leadingZeros == std::string::npos)
        return "0";
    if (leadingZeros != 0)
        minValue.erase(0, leadingZeros);

    return minValue == initValue ? "0" : minValue;
}
