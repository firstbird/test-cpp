class Solution {
public:
    int compress(vector<char>& chars) {
	    int write = 0;
	    int n = chars.size();
	    int start = 0;
	    for (int read = 0; read < n; read++) {
		    if (read == n - 1 || chars[read + 1] != chars[read]) {
			chars[write++] = chars[start];
			if (read > start) {
				int num = read - start + 1;
				string snum = to_string(num);
				for (char c : snum)
				chars[write++] = c;
			}    	
		        start = read + 1;
		    }
	    }
	    return write;
    }
};