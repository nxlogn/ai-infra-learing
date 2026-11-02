#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode *root) {
        string res;
        buildString(root, res);
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data) {
        queue<string> tokens;
        string cur;
        for (char c : data) {
            if (c == ',') {
                tokens.push(cur);
                cur.clear();
            } else {
                cur += c;
            }
        }
        if (!cur.empty()) tokens.push(cur);
        return buildTree(tokens);
    }
private:
    // 给定root序列，生成string
    void buildString(TreeNode *root, string &res) {
        if (root == nullptr) {
            res += "#,";
            return;
        }
        res += to_string(root->val) + ",";
        buildString(root->left, res);
        buildString(root->right, res);
    }

    // 给定string，生成root序列
    TreeNode* buildTree(queue<string> &tokens) {
        if (tokens.empty()) return nullptr;
        string s = tokens.front();
        tokens.pop();
        if (s == "#") return nullptr;
        TreeNode *node = new TreeNode(stoi(s));
        node->left = buildTree(tokens);
        node->right = buildTree(tokens);
        return node;
    }
};