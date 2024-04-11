
#define INT_MIN 0x80000000

class Solution {
public:
    int maxProfit(vector<int>& prices) {
	    if (prices.size() == 0) return 0;
	    int min = prices[0];
	    int res = 0;
	    for (int i = 1; i < prices.size(); i++) {
		    min = std::min(min, prices[i]);
		    res = std::max(res, prices[i] - min);
	    }
	    return res;
    }
};