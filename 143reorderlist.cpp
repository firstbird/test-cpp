
#include <unordered_map>

using namespace std;
class Solution {
public:
 struct ListNode {
     int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

    unordered_map<ListNode *, ListNode *> map;

    void reorderList(ListNode *head)
    {
	    if (head == nullptr)
		    return;
	    ListNode *p = head;
	    ListNode *pre = nullptr;
	    int count = 0;
	    while (p != nullptr) {
	            map[p] = pre;
		    pre = p;
		    p = p->next;
		    count++;
	    }
	    count /= 2;
	    p = head;
	    ListNode* q = pre;
	    while (count > 0)
	    {
		    ListNode* next = p->next;
		    p->next = q;
		    q->next = next;
		    q = map[q];
            p = next;
		    count--;
	    }
        if (p != nullptr) {
            p->next = nullptr;
        }
	    return;
    }
};