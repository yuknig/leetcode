#pragma once
#include <deque>
#include <vector>

inline int countStudents(const std::vector<int>& students, const std::vector<int>& sandwiches) {

    std::deque<int> dStudents { students.begin(), students.end() };
    std::vector<int> dSandwiches {sandwiches.rbegin(), sandwiches.rend() };
    bool changed = false;

    do {
        changed = false;

        const size_t studentsCount = dStudents.size();

        for (size_t s = 0u; s < studentsCount; ++s) {
            const int topStudent = dStudents.front();
            dStudents.pop_front();

            if (topStudent == dSandwiches.back()) {
                dSandwiches.pop_back();
                changed = true;
                break;
            }
            else
                dStudents.push_back(topStudent);
        }

    } while (!dStudents.empty() && changed);

    return dStudents.size();
}
