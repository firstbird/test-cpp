


//vector 123

//vector 345

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int findDupNum(vector<int> &A, vector<int> &B)
{
	int m = A.size();
	int n = B.size();
	std::sort(A.begin(), A.end());
	std::sort(B.begin(), B.end());
	int i = 0;
	int j = 0;
	int count = 0;
	while (i < m && j < n) {
		if (A[i] == B[j]) {
			++count;
			++i;
			++j;
			cout << "path 1" << endl;
		} else if (A[i] > B[j]) {
			++j;
			cout << "path 2" << endl;
		} else {
			++i;
			cout << "path 3" << endl;
		}
	}
	return count;
}

int main() {
	vector<int> a = {1, 2, 3, 4};
	vector<int> b = {2, 3, 5};
	int res = findDupNum(a, b);
	cout << res << endl;
}
