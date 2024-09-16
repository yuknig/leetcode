#pragma once
#include <map>
#include <unordered_set>
#include <vector>

//inline int minIncrementForUnique(const std::vector<int>& nums) {
    /*std::map<int, uint32_t> m;

    for (int n : nums)
    {
        auto [it, added] = m.emplace(n, 1u);
        if (!added)
        {
            ++it->second;
        }
    }

    int result = 0;
    size_t elmNum = 0u;
    for (auto it = m.begin(); it != m.end(); ++it, ++elmNum)
    {
        auto [value, numValues] = *it;

        if (numValues > 1)
        {
            if (m.size() - elmNum == m.rbegin()->first - value + 1)
            {
                while (numValues > 1)
                {
                    auto curValue = m.rbegin()->first + 1;
                    result += curValue - value;
                    m.emplace_hint(m.end(), curValue, 1);
                    --numValues;
                }
                continue;
            }

            auto curIt = it;
            int curValue = value;
            do
            {
                ++curIt;
                ++curValue;

                bool found = false;
                if (curIt != m.end())
                {
                    for (; found = true && curIt != m.end(); ++curValue, ++curIt)
                    {
                        if (curValue != curIt->first)
                        {
                            curIt = m.emplace_hint(curIt, curValue, 1);
                            result += curValue - value;
                            break;
                        }
                    }
                }

                if (!found)
                {
                    curValue = m.rbegin()->first + 1;
                    m.emplace_hint(m.end(), curValue, 1);
                    curIt = std::prev(m.end());
                    result += curValue - value;
                }

                --numValues;
            } while (numValues > 1);
        }
    }
    */

    //        bool found = false;
    //        ++it;
    //        for (int nextN = n + 1; it != s.end(); ++nextN, ++it)
    //        {
    //            if (nextN != *it)
    //            {
    //                result += nextN - n;
    //                s.emplace(nextN);
    //                found = true;
    //                break;
    //            }
    //        }

    //        if (!found)
    //        {
    //            const int nextN = *s.rbegin() + 1;
    //            s.emplace(nextN);
    //            result += nextN - n;
    //        }
    //    }
    //}

    //return result;
//}

inline int minIncrementForUnique(std::vector<int> nums)
{
    std::sort(nums.begin(), nums.end());

    int result = 0;
    for (size_t i = 1; i < nums.size(); ++i)
    {
        const int prevValue = nums[i-1];
        const int oldValue = nums[i];
        if (oldValue <= prevValue)
        {
            const int newValue = prevValue + 1;
            result += newValue - oldValue;
            nums[i] = newValue;
        }
    }

    return result;
}
