#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
	    vector<vector<char>> rows;
	    for (int i = 0; i < numRows; ++i) {
		    rows.push_back(vector<char>());
	    }
	    int curRow = 0;
	    int dir = -1;
	    for (char c : s) {
		    rows[curRow].push_back(c);
		    if (curRow == 0 || curRow == numRows - 1) {
			    dir = -dir;
		    }
		    curRow += dir;
	    }
	    string res;
	    for (auto row : rows) {
		    for (auto value : row) {
			    res.push_back(value);
		    }
	    
	    }
	    return res;
    }
};