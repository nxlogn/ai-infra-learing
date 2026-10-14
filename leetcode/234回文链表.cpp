#include <bits/stdc++.h>

struct ListNode
{
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

using namespace std;

class Solution {
public:
    bool isPalindrome(ListNode* head) {
      // 一个节点或没有节点
      if (head == nullptr || head->next == nullptr) return true;

      // 找到中点
      ListNode* slow = head;
      ListNode* fast = head;

      while (fast->next != nullptr && fast->next->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
      }

      // 反转slow.next及其之后的链表
      ListNode* prev = nullptr;
      ListNode* cur = slow->next;
      while (cur != nullptr) {
        ListNode* nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
      }

      // 对比两个链表
      ListNode* p2 = prev;
      ListNode* p1 = head;
      while (p2 != nullptr) {
        if (p2->val != p1->val) {
          return false;
        }
        p2 = p2->next;
        p1 = p1->next;
      }
      return true;
    }
};