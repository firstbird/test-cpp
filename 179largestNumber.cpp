#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    string largestNumber(vector<int>& nums) {
	    int n = nums.size();
	    string res;
	    sort(nums.begin(), nums.end(), cmp);
	    for (auto& num : nums) {
		    //char aChar = '0' + num;
		    res += to_string(num);
            
	    }
            //int test = stoi("1123");
	    int i = 0;
	    while (res[i] == '0')
	    {
		    i++;
	    }
	    if (i == res.size())
		    return "0";
	    return res.substr(i, res.size() - i);
    }

    static bool cmp(const int& a, const int& b) {
	string s1 = "";
	    s1 += to_string(a);
        s1 += to_string(b);
	    string s2;
	    s2 += to_string(b);
        s2 += to_string(a);
	    return s1 > s2;
    }
};