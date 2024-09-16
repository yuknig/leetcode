#pragma once
#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

inline ListNode* removeNodes(ListNode* head) {

    std::vector<int> maxValues;
    auto* node = head;
    while (node) {
        maxValues.push_back(node->val);
        node = node->next;
    }

    if (maxValues.empty())
        return nullptr;

    int maxV = maxValues.back();
    for (auto it = maxValues.rbegin(); it != maxValues.rend(); ++it) {
        maxV = std::max(maxV, *it);
        *it = maxV;
    }

    std::vector<ListNode*> filteredNodes;

    {
        size_t i = 0;
        node = head;
        while (node) {
            if (node->val >= maxValues[i])
                filteredNodes.push_back(node);
            node = node->next;
            ++i;
        }
    }

    for (size_t i = 1; i < filteredNodes.size(); ++i)
        filteredNodes[i - 1]->next = filteredNodes[i];
    filteredNodes.back()->next = nullptr;

    return filteredNodes.front();
}
