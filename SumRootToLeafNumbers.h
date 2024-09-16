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

void Visit(TreeNode* node, int curNumber) {
    curNumber += node->val;

    if (auto* leftNode = node->left)
        Visit(leftNode, curNumber*10);
    if (auto* rightNode = node->right)
        Visit(rightNode, curNumber*10);
    else if (!node->left)
        sum += curNumber;
}

inline int sumNumbers(TreeNode* root) {
    if (!root)
        return 0;

    sum = 0;
    Visit(root, 0);

    return sum;
}
