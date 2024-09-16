#pragma once
#include <string>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    
};

std::optional<std::string> minStr;
std::string leafStr;

void Visit(TreeNode* node, std::string& curString) {
    curString += 'a' + node->val;

    if (node->left)
        Visit(node->left, curString);

    if (node->right)
        Visit(node->right, curString);
    else if (!node->left && (!minStr.has_value() || curString.size() <= minStr->size())) {
        leafStr.assign(curString.crbegin(), curString.crend());
        if (minStr.has_value()) {
            if (leafStr < minStr)
                minStr = leafStr;
        }
        else
            minStr = leafStr;
    }

    curString.pop_back();
}

inline std::string smallestFromLeaf(TreeNode* root) {
    minStr = std::nullopt;

    std::string curStr;
    Visit(root, curStr);

    return *minStr;
}
