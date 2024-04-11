class Solution {
public:
    string compressString(string S) {
	    string res = "";
	    int count = 0;
	    int n = S.length();
	    char pre = 0;
	    for (int i = 0; i < n; i++) {
		    if (pre != S[i]) {
				if (pre != 0) {
				res += pre;
				res += to_string(count);
				}
				count = 1;
				pre = S[i];
		    } else {
			    count++;
		    }
	    }
            res += pre;
	    res += to_string(count);
	    return res.size() < n ? res : S;
    }
};