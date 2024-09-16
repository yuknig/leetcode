#pragma once
#include <algorithm>

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}    
};

int Visit(const TreeNode* node, int depth)
{
    int leftDepth = 0;
    int rightDepth = 0;

    if (node->left)
        leftDepth = Visit(node->left, depth + 1);
    if (node->right)
        rightDepth = Visit(node->right, depth + 1);

    return std::max({leftDepth, rightDepth, depth});
}

int maxDepth(TreeNode* root) {
    return Visit(root, 1);
}
