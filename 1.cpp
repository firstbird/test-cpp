#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <deque>

using namespace std;
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
	    unordered_map<int, int> map;
	    unordered_set<int, int> set;
	    deque<int> que;
	    vector<int>::iterator it = nums.begin();
	    for (; it < nums.end(); it++) {
		    int num = *it;
		    auto other = map.find(target - num);
		    if (other != map.end()) {
			    return {other->second, static_cast<int>(it - nums.begin())};
		    }
		    map[num] = static_cast<int>(it - nums.begin()); 
	    }

	    return {};
	    
    }
};