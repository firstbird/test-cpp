#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {

public:

    bool wordBreak(string s, vector<string>& wordDict) {
	    int n = s.size();
	    vector<bool> dp(9, false);
	    dp[0] = true;
	    bool res = false;
	    for (int i = 1; i <= n; ++i) {
		    string sub = s.substr(0, i);
		    for(auto& word : wordDict) {
			    if (i >= word.size() && sub.rfind(word) == i - word.size()) {
				    dp[i] = dp[i] || dp[i - word.size()];
			    }
		    }
	    }
	    return dp[n];
    }
};