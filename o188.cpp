struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class Solution
{
public:
	ListNode *deleteNode(ListNode *head, int val)
	{
		ListNode *dummy = new ListNode();
		dummy->next = head;
		ListNode *p = head;
		ListNode *pre = dummy;
		while (p != nullptr)
		{
			if (p->val == val)
			{
				pre->next = p->next;
				break;
			}
			else
			{
				pre = p;
				p = p->next;
			}
		}
		return dummy->next;
	}
};
