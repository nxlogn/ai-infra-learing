#include <bits/stdc++.h>

using namespace std;
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct cmp {
  bool operator()(ListNode *a, ListNode *b) { return a->val > b->val; }
};
class Solution {
public:
  ListNode *mergeKLists(vector<ListNode *> &lists) {
    // 最小堆
    priority_queue<ListNode *, vector<ListNode *>, cmp> pq;

    // 将每个链表的头节点加入堆
    for (int i = 0; i < lists.size(); i++) {
      if (lists[i] != nullptr) {
        pq.push(lists[i]);
      }
    }

    // 方便处理头节点
    ListNode *dummy = new ListNode(-1);
    ListNode *cur = dummy;

    // 不断取出当前最小
    while (!pq.empty()) {
      // 取堆顶
      ListNode *node = pq.top();
      pq.pop();

      // 接到结果链表
      cur->next = node;
      cur = cur->next;

      // 如果当前节点后面还有节点，加入堆
      if (node->next != nullptr) {
        pq.push(node->next);
      }
    }

    return dummy->next;
  }
};

// 辅助函数：根据数组构造链表
ListNode *createList(const vector<int> &vals) {
  ListNode *dummy = new ListNode(-1);
  ListNode *cur = dummy;
  for (int v : vals) {
    cur->next = new ListNode(v);
    cur = cur->next;
  }
  return dummy->next;
}

// 辅助函数：打印链表
void printList(ListNode *head) {
  while (head != nullptr) {
    cout << head->val;
    if (head->next)
      cout << "->";
    head = head->next;
  }
  cout << endl;
}

int main() {
  Solution s;

  // 测试用例1
  {
    vector<ListNode *> lists = {createList({1, 4, 5}), createList({1, 3, 4}),
                                createList({2, 6})};
    cout << "用例1: ";
    printList(s.mergeKLists(lists));
  }

  // 测试用例2：空链表
  {
    vector<ListNode *> lists = {};
    cout << "用例2: ";
    printList(s.mergeKLists(lists));
  }

  // 测试用例3：只有一个链表
  {
    vector<ListNode *> lists = {createList({1})};
    cout << "用例3: ";
    printList(s.mergeKLists(lists));
  }

  // 测试用例4：nullptr 元素
  {
    vector<ListNode *> lists = {nullptr, createList({1, 2}), nullptr};
    cout << "用例4: ";
    printList(s.mergeKLists(lists));
  }

  return 0;
}
