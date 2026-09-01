#include <bits/stdc++.h>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
  // 递归函数的定义：在root的树中找p和q
  {
    if (root == nullptr || root == p || root == q)
    {
      return root;
    }

    // 去左右子树找
    TreeNode *left = lowestCommonAncestor(root->left, p, q);
    TreeNode *right = lowestCommonAncestor(root->right, p, q);

    // 左右都找到了，说明root是最近公共祖先
    if (left != nullptr && right != nullptr)
    {
      return root;
    }

    // 哪边找到了，就往上传哪边
    return left != nullptr ? left : right;
  }
};

int main()
{
}
