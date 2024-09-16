#pragma once

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* ReverseList(ListNode* head)
{
    auto* prev = head;
    auto* node = head->next;
    head->next = nullptr;

    while (node) {
        auto* nodeNext = node->next;
        node->next = prev;
        prev = node;
        node = nodeNext;
    }

    return prev;
}

inline ListNode* doubleIt(ListNode* head) {
    head = ReverseList(head);

    int rem = 0;

    auto* node = head;
    auto* lastNode = head;
    while (node) {
        int newVal = node->val * 2 + rem;
        if (newVal >= 10) {
            newVal -= 10;
            rem = 1;
        }
        else
            rem = 0;

        node->val = newVal;
        node = node->next;
        if (node)
            lastNode = node;
    }

    if (rem) {
        auto newNode = new ListNode(rem);
        lastNode->next = newNode;
    }

    head = ReverseList(head);
    return head;
}
