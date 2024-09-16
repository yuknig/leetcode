#pragma once
#include <numeric>
#include <vector>

//https://leetcode.com/problems/find-valid-matrix-given-row-and-column-sums

std::vector<std::vector<int>> restoreMatrix(const std::vector<int>& rowSum, const std::vector<int>& colSum) {

    const auto rowCount = rowSum.size();
    const auto colCount = colSum.size();

    std::vector<std::vector<int>> result(rowCount);
    for (auto& row : result)
        row.resize(colCount, 0);

    result[0] = colSum;

    size_t colStart = 0;

    for (size_t rowNum = 1; rowNum < rowCount; ++rowNum)
    {
        auto& resultRow = result[rowNum];

        int leftForRow = rowSum[rowNum];
        for (size_t colNum = colStart; colNum < colCount; ++colNum)
        {
            int& firstCellOfCol = result[0][colNum];
            if (firstCellOfCol <= leftForRow)
            {
                leftForRow -= firstCellOfCol;
                resultRow[colNum] = firstCellOfCol;
                firstCellOfCol = 0;
                colStart = colNum + 1;
            }
            else
            {
                resultRow[colNum] = leftForRow;
                firstCellOfCol -= leftForRow;
                leftForRow = 0;
                break;
            }
        }
    }

    return result;
}
