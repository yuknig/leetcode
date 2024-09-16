#pragma once
#include <string>
#include <vector>

inline std::vector<std::string> FullJustify(const std::vector<std::string>& words, int maxWidth) {
    std::vector<std::string> lines;

    size_t startWord = 0;
    std::string curLine;
    while (startWord < words.size()) {
        size_t curLineLen = words[startWord].size();

        // find last word that fits current line
        size_t lastWord = words.size() - 1;
        for (size_t wordNum = startWord + 1; wordNum < words.size(); ++wordNum) {
            const size_t nextLineLen = curLineLen + 1 + words[wordNum].size();
            if (nextLineLen > maxWidth) {
                lastWord = wordNum - 1;
                break;
            }
            curLineLen = nextLineLen;
        }

        // from line
        std::string curLine;
        curLine.reserve(static_cast<size_t>(maxWidth));

        curLine.assign(words[startWord]);

        const size_t wordCount = lastWord - startWord + 1;
        size_t lettersCount = curLineLen;
        if (wordCount > 1)
            lettersCount -= wordCount - 1;
        const int spaceCount = maxWidth - static_cast<int>(lettersCount);

        assert(wordCount > 0);
        if (lastWord + 1 == words.size() || wordCount == 1) {
            for (size_t wordNum = 1; wordNum < wordCount; ++wordNum) {
                curLine.append(1, ' ');
                curLine.append(words[startWord + wordNum]);
            }
            curLine.append(maxWidth - curLine.size(), ' ');
        }
        else {
            const std::div_t div_mod = std::div(spaceCount, static_cast<int>(wordCount - 1));
            for (size_t wordNum = 1; wordNum < wordCount; ++wordNum) {
                int sepLength = div_mod.quot;
                if (wordNum <= div_mod.rem)
                    ++sepLength;
                curLine.append(static_cast<size_t>(sepLength), ' ');
                curLine.append(words[startWord + wordNum]);
            }
        }

        assert(curLine.size() == maxWidth);
        lines.push_back(std::move(curLine));

        startWord = lastWord + 1;
    }

    return lines;
}
