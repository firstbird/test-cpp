  struct ListNode {
      int val;
      ListNode* next;
      ListNode(int x) : val(x), next(NULL) {}
  };
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
	    ListNode* dummy = new ListNode();
	    ListNode* p = dummy;
	    ListNode* p1 = l1;
	    ListNode* p2 = l2;
	    while (p1 != nullptr && p2 != nullptr) {
		    if (p1->val < p2->val) {
			    ListNode* next = new ListNode(p1->val);
			    p->next = next;
			    p = next;
                p1 = p1->next;
		    } else {
			    ListNode* next = new ListNode(p2->val);
			    p->next = next;
			    p = next;
                p2 = p2->next;
		    }
	    }
	    if (p1 == nullptr) {
		    p->next = p2; 
	    }
	    if (p2 == nullptr) {
		    p->next = p1; 
	    }
	    return dummy->next;
    }
};