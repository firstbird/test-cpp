class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
	    vector<int> res;
	    if (k == 0) {
		    return res;
	    }
	    priority_queue<int> queue;
	    for (int i = 0; i < arr.size(); i++) {
		    queue.push(arr[i]);
		    if (queue.size() > k) {
			    queue.pop();
		    }
	    }
	    int i = 0;
	    while (queue.size() != 0) {
		    res.push_back(queue.top());
            	    queue.pop();
	    }
	    return res;
    }
};