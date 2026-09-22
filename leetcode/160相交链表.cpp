#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    /*
    A指针走到nullptr去到B
    B指针走到nullptr去到A
    A=B时就是入口
    */
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
      if (headA == nullptr && headB == nullptr) return nullptr;

      ListNode* p = headA;
      ListNode* q = headB;

      while (p != q) {
        p = (p == nullptr) ? headB : p->next;
        q = (q == nullptr) ? headA : q->next;
      }

      return q;
    }
};

int main() {
    Solution solution;
    
    return 0;
}
