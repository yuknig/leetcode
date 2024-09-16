#pragma once

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

int sum;

void Visit(TreeNode* node, bool isLeft)
{
    if (node->left) {
        Visit(node->left, true);
    }

    if (node->right) {
        Visit(node->right, false);
    }
    else if (isLeft && !node->left)
        sum += node->val;
}

inline int sumOfLeftLeaves(TreeNode* root) {
    if (!root)
        return 0;

    sum = 0;
    if (root->left)
        Visit(root->left, true);

    if (root->right)
        Visit(root->right, false);

    return sum;
}
