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
    1. 双指针 指针fast一次2步，slow一次1步
    2. 相遇之后设置其中一个为head，同步走就会在入口相遇
    */
    ListNode *detectCycle(ListNode *head) {
      ListNode* fast = head;
      ListNode* slow = head;

      while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;

        if (fast == slow) {
          ListNode* p = head;
          ListNode* p2 = slow;
          while (p != p2) {
            p = p->next;
            p2 = p2->next;
          }
          return p;
        }
      }
      return nullptr;
    }
};

int main() {
    Solution solution;
    
    return 0;
}
