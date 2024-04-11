
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
	    sort(intervals.begin(), intervals.end(), cmp);
	    vector<int> cur = intervals[0];
	    vector<vector<int>> res;
	    res.emplace_back(cur);
	    for (int i = 1; i < intervals.size(); ++i) {
		    int nextBegin = intervals[i][0];
		    int nextEnd = intervals[i][1];
		    if (nextBegin <= res.back()[1]) {
			//     cur[1] = max(nextEnd, cur[1]);
			    res.back()[1] = max(nextEnd, res.back()[1]);
		    } else {
			    cur = intervals[i];
			    res.emplace_back(cur);
		    }
	    }
	    return res;
    }

    static bool cmp(const vector<int>& a, const vector<int>& b) {
	    return a[0] < b[0];
    }
    public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
	    sort(intervals.begin(), intervals.end(), cmp);
	    vector<int> cur = intervals[0];
	    vector<vector<int>> res;
	    res.emplace_back(cur);
	    for (int i = 1; i < intervals.size(); ++i) {
		    int nextBegin = intervals[i][0];
		    int nextEnd = intervals[i][1];
		    if (nextBegin <= cur[1]) {
			//     cur[1] = max(nextEnd, cur[1]);
			    res.back()[1] = max(nextEnd, cur[1]);
		    } else {
			    cur = intervals[i];
			    res.emplace_back(cur);
		    }
	    }
	    return res;
    }

    bool cmp(const vector<int>& a, const vector<int>& b) {
	    return a[0] < b[0];
    }
};