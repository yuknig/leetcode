#pragma once
#include <bitset>
#include <string>
#include <vector>

constexpr int MaxW = 6;
constexpr int MaxH = 6;

int H, W;
std::bitset<MaxW* MaxH> CellUsed;
const std::vector<std::vector<char>>* Board;
std::string Word;

inline bool Walk(int x, int y, int charNum)
{
    ++charNum;
    if (charNum == Word.size())
        return true;

    const size_t cellOffset = y*W + x;
    CellUsed[cellOffset] = true;

    const char nextCh = Word[charNum];

    const auto& row = (*Board)[y];
    if (x > 0 && row[x-1] == nextCh && !CellUsed[cellOffset-1])
        if (Walk(x-1, y, charNum))
            return true;

    if (x + 1 < W && row[x+1] == nextCh && !CellUsed[cellOffset+1])
        if (Walk(x+1, y, charNum))
            return true;

    if (y > 0 && (*Board)[y-1][x] == nextCh && !CellUsed[cellOffset-W])
        if (Walk(x, y-1, charNum))
            return true;

    if (y+1 < H && (*Board)[y + 1][x] == nextCh && !CellUsed[cellOffset+W])
        if (Walk(x, y+1, charNum))
            return true;

    CellUsed[cellOffset] = false;
    return false;
}


inline bool WordExist(const std::vector<std::vector<char>>& board, std::string word) {
    if (word.empty())
        return false;

    H = static_cast<int>(board.size());
    if (!H)
        return false;

    W = static_cast<int>(board[0].size());
    if (!W)
        return false;

    Board = &board;
    Word = word;
    CellUsed.reset();

    const char firstCh = word[0];
    for (int y = 0; y < H; ++y) {
        const auto& row = board[y];
        for (int x = 0; x < W; ++x) {
            const char ch = row[x];
            if (ch == firstCh) {
                // launch search

                if (Walk(x, y, 0))
                    return true;
            }
        }
    }

    return false;
}
