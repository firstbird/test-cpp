#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
	    int left = n;
	    int right = n;
	    vector<string> res;
	    dfs("", left, right, res);
    }

    void dfs(string cur, int left, int right, vector<string>& res) {
	    if (left == 0 && right == 0) {
		    res.push_back(cur);
		    return;
	    }
	    if (left > right) {
		    return;
	    }
	    if (left > 0) {
		    dfs(cur + "(", left - 1, right, res);
	    }
	    if (right > 0) {
		    dfs(cur + ")", left, right - 1, res);
	    }
    }
};