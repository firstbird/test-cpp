#include <cstring>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;
class Solution {
private:
    int mem[200][200];
    int _m;
    int _n;  

    unordered_map<int, vector<int>> relation;
    unordered_set<int> visited;
public:
    int minPathSum(vector<vector<int>>& grid) {
        _m = grid.size();
        _n = grid[0].size();
        if (_m > 200 || _n > 200) {
            return 0;
        }
        // for(int i=0;i<200;i++){
        // for(int j=0;j<200;j++){
        //     mem[i][j]=-1;
        // }
        // }
        memset(mem, -1, sizeof(mem));
        int x = 0;
        int y = 0;

        return dfs(grid, x, y);
        //return mem[0][0];
    }

    int dfs(vector<vector<int>>& grid, int x, int y) {
        if (x == _m -1 && y == _n -1) {
            return grid[_m - 1][_n - 1];
        }
        if (x >= _m || y >= _n) {
            //mem[startX][startY] = Integer.MAX_VALUE;
            return INT_MAX;
        }
        // if (x >= _m || x < 0 || y >= _n || y < 0) {
        //     return 0;
        // }
        if (mem[x][y] != -1) {
            return mem[x][y];
        }
        int min = grid[x][y] + std::min(dfs(grid, x + 1, y), dfs(grid, x, y+ 1));
        mem[x][y] = min;
        return min;
    }


    template <size_t m, size_t n>
    int findCircleNum(int (&M)[m][n]) {
        if (m == 0) {
            return 0;
        }
        //int n = M[0].length;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
               if (i != j && M[i][j] == 1) {
                   relation[i].push_back(j);
                   //    List listI = relation.getOrDefault(i, new ArrayList<>());
                   //    if (!listI.contains(j)) {
                   //       listI.add(j);
                   //       relation.put(i, listI);
                   //    }
                   //    List listJ = relation.getOrDefault(j, new ArrayList<>());
                   //    if (!listJ.contains(i)) {
                   //        listJ.add(i);
                   //        relation.put(j, listJ);
                   //    }
                   relation[j].push_back(i);
               }
            }
        }
        int count = 0;
         for (int i = 0; i < m; i++) {
             auto& neighbours = relation[i];
             vector<int> members;
             if (visited.find(i) == visited.end()) {
                 members.push_back(i);
                 visited.insert(i);
             }
             dfs(neighbours, members);
             if (!members.empty()) {
                 count++;
             }
         }
         return count;
    }

    void dfs(vector<int>& neighbours, vector<int>& members) {
        if (neighbours.empty()) {
            return;
        }
        for (int nei: neighbours) {
           if (visited.find(nei) == visited.end()) {
               visited.insert(nei);
               members.push_back(nei);
               dfs(relation[nei], members);
           }
        }
    }
};

int main() {
	Solution s;
	vector<vector<int>> grid = 
	{{1,3,1},{1,5,1},{4,2,1}};
	cout << s.minPathSum(grid) << endl;

    int m[3][3] = { {1, 1, 0 },
                  { 1, 1, 0 },
                  { 0, 0, 1 }};
    cout << s.findCircleNum(m) << endl;
}