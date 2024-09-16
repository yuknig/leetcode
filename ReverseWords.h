#pragma once
#include <string>
#include <vector>

//inline std::string reverseWords(const std::string& s) {
//    std::string result;
//
//    size_t pos = 0u;
//
//    while (pos < s.size()) {
//        const size_t startPos = s.find_first_not_of(' ', pos);
//        if (startPos == std::string::npos)
//            break;
//
//        const size_t endPos = s.find_first_of(' ', startPos);
//
//        if (!result.empty())
//            result += ' ';
//        result += s.substr(startPos, endPos - startPos);
//
//        pos = endPos;
//        if (endPos != std::string::npos)
//            ++pos;
//    }
//
//    return result;
//}

inline std::string reverseWords(const std::string& s) {
    std::string result;
    size_t length = s.length();

    while (true) {
        const size_t wordEnd = s.find_last_not_of(' ', length);
        if (wordEnd == std::string::npos)
            break;

        size_t wordStart = s.find_last_of(' ', wordEnd);
        if (wordStart == std::string::npos)
            wordStart = 0;
        else
            ++wordStart;

        if (!result.empty())
            result += ' ';
        result += s.substr(wordStart, wordEnd - wordStart + 1);
        if (wordStart > 0)
            length = wordStart - 1;
        else
            break;
    }

    return result;
}
