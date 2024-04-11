#include <iostream>
#include <vector>
#include <algorithm>

#include <unordered_map>
using namespace std;

class Solution {
public:
	int vis[101];

	int cost = INT_MAX;
	int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k)
	{
		vector<vector<int>> map(n, vector<int>(n, 0));
		for (auto f : flights) {
			map[f[0]][f[1]] = f[2];
		}
		dfs(src, k + 1, map, dst, 0);
		if (cost == INT_MAX)
			return -1;
		return cost;
	}

	void dfs(int start, int k, vector<vector<int>> &map, int dst, int curCost)
	{
		if (k == 0) {
			return;
		}
		if (start == dst) {
			cost = min(cost, curCost);
			return;
		}
		for (int j = 0; j < map[start].size(); j++) {
			if (map[start][j] > 0) {
				if (vis[j] == 1)
					continue;
				if (curCost + map[start][j] > cost)
					continue;
				vis[j] = 1;
				dfs(j, k - 1, map, dst, curCost + map[start][j]);
				vis[j] = 0;
			}

		}
	}
};