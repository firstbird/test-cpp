
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
 
class Solution {
public:
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

  	unordered_map<int, int> inorderMap;
  	TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
  	{
		int i = 0;
		for (auto in : inorder)
		{
			inorderMap[in] = i++;
		}
		int preRoot = 0;
		int inStart = 0;
		int inEnd = inorder.size() - 1;
		return dfs(preorder, preRoot, inStart, inEnd);
	}

	TreeNode* dfs(vector<int> &preorder, int preRoot, int inStart, int inEnd) {
		if (inStart > inEnd) {
			return nullptr;
		}
		TreeNode *root = new TreeNode(preorder[preRoot]);
		int rootIndexInOrder = inorderMap[preorder[preRoot]];
		int leftSize = rootIndexInOrder - inStart;
		root->left = dfs(preorder, preRoot + 1, inStart, inStart + leftSize - 1);
		root->right = dfs(preorder, preRoot + leftSize + 1, inStart + leftSize + 1, inEnd);
		return root;
	}
};