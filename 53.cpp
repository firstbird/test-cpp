class Solution {
public:
    int maxSubArray(vector<int>& nums) {
	    int n = nums.size();
	    if (n == 0) return 0;
	    int dp[n];
	    dp[0] = nums[0];
	    int max = dp[0];
	    for (int i = 1; i < n; i++) {
		    dp[i] = std::max(nums[i], dp[i - 1] + nums[i]); 
		    max = std::max(max, dp[i]);
	    }
	    return max;
    }
};