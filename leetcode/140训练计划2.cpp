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
    ListNode* trainingPlan(ListNode* head, int cnt) {
        ListNode* fast = head;
        ListNode* slow = head;

        // fast 先走 cnt 步
        for (int i = 0; i < cnt; i++)
        {
          fast = fast->next;
        }

        // fast 走到末尾，slow正好是
        while (fast != nullptr)
        {
          fast = fast->next;
          slow = slow->next;
        }
        return slow;
    }
};