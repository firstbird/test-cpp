
#include <string>
#include <vector>
#include <set>
#include <iostream>
using namespace std;

class Solution {
public:
	vector<vector<int>> res;
	set<int> visited;
	vector<vector<int>> permute(vector<int> &nums)
	{
		int count = 0;
		vector<int> tmp;
		dfs(count, nums, tmp);
		return res;
	}

private:
	void dfs(int count, vector<int> &nums, vector<int> tmp) {
		if (count == nums.size()) {
			res.push_back(vector<int>(tmp));
			return;
		}
		for (int& num : nums) {
			if (visited.count(num) == 0) {
				tmp.push_back(num);
				visited.insert(num);
				dfs(count + 1, nums, tmp);
				tmp.pop_back();
				visited.erase(num);
			}
		}
	}
};