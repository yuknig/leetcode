#pragma once
#include <list>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

int neededDepth;
int neededVal;

void Visit(TreeNode* curNode, int curDepth) {

    if (curDepth + 1 == neededDepth) {

        if (curNode->left) {
            auto* newNode = new TreeNode(neededVal, curNode->left, nullptr);
            curNode->left = newNode;
        } else
            curNode->left = new TreeNode(neededVal);

        if (curNode->right) {
            auto* newNode = new TreeNode(neededVal, nullptr, curNode->right);
            curNode->right = newNode;
        } else
            curNode->right = new TreeNode(neededVal);

        return;
    }

    if (curNode->left)
        Visit(curNode->left, curDepth + 1);
    if (curNode->right)
        Visit(curNode->right, curDepth + 1);
}


inline TreeNode* addOneRow(TreeNode* root, int val, int depth) {
    if (!root)
        return nullptr;

    if (depth == 1) {
        auto* newNode = new TreeNode(val, root, nullptr);
        return newNode;
    }

    neededDepth = depth;
    neededVal = val;

    Visit(root, 1);

    return root;
}
