#include <iostream>
#include <vector>
#include <algorithm>

#include <unordered_map>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
	    unordered_map<int, int> freq;
	    for (int num : nums) {
		    freq[num]++;
	    }
	    int ans = 0;
	    for (auto [num, f] : freq) {
		    if (f == 1) {
			    ans = num;
			    break;
		    }
	    }
	    return ans;
    }
};
