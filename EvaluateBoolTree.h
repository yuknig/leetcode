#pragma once
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

bool Visit(const TreeNode* node)
{
    switch (node->val) {
    case 0:
        return false;
    case 1:
        return true;
    case 2:
        return Visit(node->left) || Visit(node->right);
    case 3:
    {
        if (!Visit(node->left))
            return false;
        return Visit(node->right);
    }
    }

    return false;
}

inline bool evaluateTree(const TreeNode* root) {
    return Visit(root);
}
