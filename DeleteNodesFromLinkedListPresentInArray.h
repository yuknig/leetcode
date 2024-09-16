#pragma once
#include <vector>
#include <unordered_set>

// https://leetcode.com/problems/delete-nodes-from-linked-list-present-in-array

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* modifiedList(std::vector<int>& nums, ListNode* head) {
        const std::unordered_set<int> numsSet(nums.begin(), nums.end());

        auto* newHead = head;
        while (numsSet.count(newHead->val))
            newHead = newHead->next;

        auto* lastNode = newHead;
        auto* node = newHead->next;
        while (node)
        {
            if (numsSet.count(node->val))
                lastNode->next = node->next;
            else
                lastNode = node;
            node = node->next;
        }

        return newHead;
    }
};
