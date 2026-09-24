#include <bits/stdc++.h>
#include <cstddef>
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
    1. 双指针，指针p先走n步，然后p和q同时走
    2. 当p的next为nullptr时，q就是需要删除的节点的前一个结点
    3. 改变链接即删除
    */
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy = ListNode(-1, head);
        ListNode* p = &dummy;
        ListNode* q = &dummy;

        while (n--) {
          p = p->next;
        }

        while (p->next) {
          p = p->next;
          q = q->next;
        }

        q->next = q->next->next;

        return dummy.next;
    }
};