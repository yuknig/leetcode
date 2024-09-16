#pragma once

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

int Target;

void Visit(TreeNode* parent, TreeNode* node)
{
    if (node->left)
        Visit(node, node->left);
    if (node->right)
        Visit(node, node->right);

    if (node->val == Target && !node->left && !node->right && parent) {
        if (parent->left == node)
            parent->left = nullptr;
        else
            parent->right = nullptr;
    }
}

TreeNode* removeLeafNodes(TreeNode* root, int target) {
    Target = target;
    Visit(nullptr, root);
}
