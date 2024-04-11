
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
	    int n = nums.size();
	    vector<int> dp(n, 0);
	    int res = 1;
	    dp[0] = 1;
	    for (int i = 1; i < n; ++i) {
		    dp[i] = 1;
		    for (int j = 0; j < i; ++j) {
			    if (nums[i] > nums[j]) {
				    dp[i] = max(dp[i], dp[j] + 1);
			    }
		    }
		    res = max(dp[i], res);
	    }
	    return res;
    }
};