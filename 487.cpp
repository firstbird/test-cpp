#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int n = nums.size();
	int left = 0;
	int max = 0;
	nums.resize(8);
	// 要注意状态尽量少
	int zeroIndex = -1;
	for (int right = 0; right < n; right++) {
	    if (nums[right] == 1) {    
		continue;    
	    }
	    // meet 0 more than once
	    if (zeroIndex != -1) {
	    	max = std::max(max, right - left);
		    //cout << "max: " << max << " right: " << right << " left: " << left << " zeroIndex: " << zeroIndex << endl;
	        left = zeroIndex + 1;
		// 要注意每个分支每个变量的变化
                zeroIndex = right;
	    } else {
		zeroIndex = right;
	    }
	}	
	max = std::max(max, n - left);
	//cout << "end max: " << max << " n: " << n << " left: " << left << endl;
	return max;
    }
};