struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool isValidBST(TreeNode *root) {
        TreeNode* prev = nullptr;
        return inorder(root, prev);
    }
private:
    // 引用传递prev节点，共享上一个节点
    bool inorder(TreeNode *node, TreeNode* &prev) {
        if (node == nullptr) {
            return true;
        }

        // 进入左边递归
        if (!inorder(node->left, prev)) {
            return false;
        }

        // 左边不能比右边大
        if (prev != nullptr && prev->val >= node->val) {
            return false;
        }
        prev = node;

        // 进入右边递归并传递给父节点
        return inorder(node->right, prev);
    }
};