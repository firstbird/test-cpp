#include <iostream>
#include <vector>
#include <algorithm>

#include<queue>
using namespace std;

class Solution {
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
	    unordered_map<int, int> counts;
	    priority_queue<pair<int, int>, vector<pair<int, int>>, less<> > queue;

	    for (int& b: barcodes) {
		    counts[b]++;
	    }
	    for (auto c : counts) {
		    queue.push({c.first, c.second});
	    }
	    int n = barcodes.size();
	    vector<int> res;
	    while (!queue.isEmpty())
	    {

		    pair<int, int> a = queue.top();
                    queue.pop();
		    pair<int, int> b = queue.top();
                    queue.pop();
	            res.push_back(a.second);
	            res.push_back(b.second);
	            if (b.first > 1) {
		        tmpQueue.push({b.first - 1, b.second});
	            }
	            if (a.first > 1) {
		        tmpQueue.push({a.first - 1, a.second});
	            }
	    }
	    return res;
        }
};