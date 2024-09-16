#pragma once
#include <algorithm>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

bool VisitNode(TreeNode* lhs, TreeNode* rhs)
{
    if ((!lhs) != (!rhs))
        return false;

    if (!lhs)
        return true;

    if ((!lhs->left) != (!rhs->left))
        return false;

    if ((!lhs->right) != (!rhs->right))
        return false;

    if (lhs->left && !VisitNode(lhs->left, rhs->left))
        return false;

    if (lhs->right && !VisitNode(lhs->right, rhs->right))
        return false;

    return true;
}

inline bool isSameTree(TreeNode* p, TreeNode* q) {
    return VisitNode(p, q);
}
