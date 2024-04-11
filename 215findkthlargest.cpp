#include <string>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
	    priority_queue<int, vector<int>, greater<int>> q;
	    for (auto num : nums) {
		    q.push(num);
		    if (q.size() > k) {
			    q.pop();
		    }
	    }
	    return q.top();
    }
};