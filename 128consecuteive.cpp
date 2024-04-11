#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
public:

    int longestConsecutive(vector<int>& nums) {
	    set<int> s;
	    for (auto num : nums) {
		    s.insert(num);
	    }
	    int res = 0;
	    for (auto key : s) {
		    if (s.count(key - 1) == 0){
			    int cur = key;
			    while (s.count(cur) != 0)
			    {
				    cur++;
			    }
			    res = max(res, cur - key);
		    }
	    }
	    return res;
    }
};