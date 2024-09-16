#pragma once
#include <cassert>
// https://leetcode.com/problems/linked-list-in-binary-tree


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution {
public:
    bool isSubPath(ListNode* head, TreeNode* root) {
        return Visit(head, root);
    }

private:
    bool Visit(ListNode* listNode, TreeNode* treeNode)
    {
        if (treeNode->val == listNode->val)
        {
            if (listNode->next)
            {
                if (treeNode->left && VisitNext(listNode->next, treeNode->left))
                    return true;

                if (treeNode->right && VisitNext(listNode->next, treeNode->right))
                    return true;
            }
            else
                return true;
        }

        if (treeNode->left && Visit(listNode, treeNode->left))
            return true;

        if (treeNode->right && Visit(listNode, treeNode->right))
            return true;

        return false;
    }

    bool VisitNext(ListNode* listNode, TreeNode* treeNode)
    {
        if (listNode->val != treeNode->val)
            return false;

        if (listNode->next)
        {
            if (treeNode->left && VisitNext(listNode->next, treeNode->left))
                return true;

            if (treeNode->right && VisitNext(listNode->next, treeNode->right))
                return true;
        }
        else
            return true;

        return false;
    }
};

