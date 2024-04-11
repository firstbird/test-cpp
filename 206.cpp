
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) return head;
	    ListNode* pre = nullptr;
	    ListNode* p = head;
	    while (p != nullptr) {
	        ListNode* tmpNext = p->next;
	        p->next = pre;
	        pre = p;	
	        p = tmpNext;
	    }
        return pre;
    }
};