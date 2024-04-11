#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
	    int n = s.size();
	    vector<vector<bool>> dp(n, vector<bool>(n + 1, false));
	    for (int i = 0; i < n; ++i) {
		    dp[i][1] = true;
	    }
	    for (int j = 2; j <= n; ++j) {
		    for (int i = 0; i + j <= n; ++i) {
			    if (j > 2) {
				    dp[i][j] = dp[i + 1][j - 2] && s[i] == s[i + j - 1];
			    } else {
				    dp[i][j] = (s[i] == s[i + j - 1]);
			    }
		    }
	    }
	    int max = 0;
	    int start = -1;
        for (int i = 0; i < n; i++) {
            for (int j = n; j >= 1; j--) {
			    if (dp[i][j] && j > max) {
				    // if () {
					    max = j;
					    start = i;
                        cout<<" j "<<j<< " max: "<<max << " start: "<< start <<endl;
					    break;
				    // }
			    }
		    }
	    }
	    if (start != -1) {
            return s.substr(start, max);
        }
		return "";
    }
};

int main()
{
	Solution s;
	cout <<s.longestPalindrome("abbacc") << endl; // Call myMax for int

	return 0;
}