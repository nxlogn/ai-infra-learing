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
    /*
    1. 创建dummynode存储结果
    2. while 双指针遍历2个链表
    3. l1.val + l2.val + carry
    */
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // 创建dummynode和cur
        ListNode dummynode = ListNode(0);
        ListNode* cur = &dummynode;

        // 进位
        int carry = 0;

        // 双指针遍历
        while (l1 != nullptr || l2 != nullptr || carry) {
            int x = l1 ? l1->val : 0;
            int y = l2 ? l2->val : 0;
            int sum = x + y + carry;
            // 重新算进位
            carry = sum / 10;
            // 当前余位
            cur->next = new ListNode(sum % 10);
            cur = cur->next;
            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
        }

        return dummynode.next;
    }
};