
#include <vector>;
#include <stack>;
using namespace std;
class Solution
{

	struct TreeNode
	{
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
	};

public:
	vector<int> rightSideView(TreeNode *root)
	{
		vector<int> res;
		if (root == nullptr)
		{
			return res;
		}
		deque<TreeNode *> q;
		q.push_back(root);
		while (!q.empty())
		{
			res.push_back(q.back()->val);
			int size = q.size();
			while (size > 0)
			{
				TreeNode *node = q.front();
				q.pop_front();
				if (node->left != nullptr)
				{
					q.push_back(node->left);
				}
				if (node->right != nullptr)
				{
					q.push_back(node->right);
				}
				size--;
			}
		}
		return res;
	}
};
