#include <bits/stdc++.h>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

using namespace std;

class Solution {
  public:
    /**
     * 双指针floyd判圈算法
     */
    bool hasCycle(ListNode *head) {
        ListNode *dummy = new ListNode(-1, head);
        ListNode *slow = dummy;
        ListNode *fast = dummy;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }

        return false;
    }
};