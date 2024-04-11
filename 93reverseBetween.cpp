 
class Solution {
public:
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
    ListNode* reverseBetween(ListNode* head, int left, int right) {
	    ListNode dummy;
	    dummy.next = head;
	    ListNode *p = &dummy;
	    ListNode *pre;
	    ListNode *post;
	    ListNode *rightNode;
	    ListNode *leftNode;
	    int lc = left - 1;
	    while (lc > 0) {
		    p = p->next;
		    --lc;
	    }
	    pre = p;
	    int rc = right - left + 1;
	    while (rc > 0) {
		    p = p->next;
		    --rc;
	    }
	    leftNode = pre->next;
	    rightNode = p;
	    post = rightNode->next;
	    pre->next = nullptr;
	    rightNode->next = nullptr;
	    reverseMid(leftNode);
	    pre->next = rightNode;
	    leftNode->next = post;
	    return dummy.next;
    }

private:
	void reverseMid(ListNode* head) {
		ListNode* p = head;
		ListNode *pre = nullptr;
		while (p != nullptr)
		{
			ListNode *next = p->next;
			p->next = pre;
			pre = p;
			p = next;
		}
		
	}
};