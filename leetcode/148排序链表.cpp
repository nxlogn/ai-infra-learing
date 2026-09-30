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
    1. 归并排序 分为两半 开始merge
    2. 递归每一半 保证有序 最后只剩一个元素的时候有序
    */
    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode* slow = head;
        ListNode* fast = head->next->next;
        
        // 找到中点，左边的最后一个位置是slow
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }

        // 断链
        ListNode* second = slow->next;
        slow->next = nullptr;

        return merge(sortList(head), sortList(second));
    }

    // 将有序链表合并
    ListNode* merge(ListNode* a, ListNode* b) {
        ListNode dummy;
        ListNode* tail = &dummy;

        while (a && b) {
            if (a->val <= b->val) {
                tail->next = a;
                a = a->next;
            } else {
                tail->next = b;
                b = b->next;
            }
            tail = tail->next;
        }

        tail->next = a ? a : b;

        return dummy.next;
    }
};