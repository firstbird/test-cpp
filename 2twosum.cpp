 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	    ListNode* dummy = new ListNode(0);
	    ListNode *p1 = l1;
	    ListNode *p2 = l2;
	    ListNode *p = dummy;
	    int carry = 0;
	    while (p1 != nullptr || p2 != nullptr)
	    {
		    int v1 = p1 != nullptr ? p1->val : 0;
		    int v2 = p2 != nullptr ? p2->val : 0;
		    int val = (v1 + v2 + carry) % 10;
		    carry = (v1 + v2 + carry) / 10;
		    p->next = new ListNode(val);
		    p = p->next;
		    if (p1 != nullptr)
			    p1 = p1->next;
		    if (p2 != nullptr)
			    p2 = p2->next;
	    }
	    if (carry != 0) {
		    p->next = new ListNode(carry);
	    }
	    return dummy->next;
    }
};