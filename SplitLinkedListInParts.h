#pragma once
#include <vector>


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    std::vector<ListNode*> splitListToParts(ListNode* head, int k) {

        const int size = Size(head);
        const int minElmsInBin = size / k;
        const int binsWithExtraElement = size - minElmsInBin * k;

        auto* node = head;
        int binNum = 0;
        int itemNumInBin = 0;

        int binCapacity = minElmsInBin;
        if (binsWithExtraElement)
            ++binCapacity;

        std::vector<ListNode*> result;
        result.reserve(k);

        while (node)
        {
            if (itemNumInBin == 0)
                result.push_back(node);
            ++itemNumInBin;

            auto* const nextNode = node->next;

            if (itemNumInBin == binCapacity)
            {
                node->next = nullptr;
                itemNumInBin = 0;
                ++binNum;
                binCapacity = minElmsInBin;
                if (binNum < binsWithExtraElement)
                    ++binCapacity;
            }

            node = nextNode;
        }

        while (static_cast<int>(result.size()) < k)
            result.push_back(nullptr);

        return result;
    }

private:
    static int Size(ListNode* node)
    {
        int size = 0;
        while (node)
        {
            ++size;
            node = node->next;
        }

        return size;
    }
};
