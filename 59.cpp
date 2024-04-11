#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
	    vector<vector<int>> res(n, vector<int>(n));
	    int max = n * n;
	    int i = 1;
	    int currentDirection = 0;
	    // right, down, left, up
	    vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}} 
	    int row = 0;
	    int col = 0;
	    while (i <= max)
	    {
		    res[row][col] = i;
		    int nextRow = row + dirs[currentDirection][0];
		    int nextCol = col + dirs[currentDirection][1];
		    if (nextRow < 0 || nextCol < 0 || nextRow >= n || nextCol >= n || res[nextRow][nextCol] != 0) {
			    currentDirection = (currentDirection + 1) % 4;
		    }
		    row = row + dirs[currentDirection][0];
		    col = col + dirs[currentDirection][1];
	    }
	    return res;
    }
};
