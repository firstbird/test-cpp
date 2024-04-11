#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
void testArray(int arr[]) {
	cout << arr[2] << endl;
}


int main() {
	int arr[3] = {1, 2, 3};
	testArray(arr);

	vector<int> a = {5, 4, 7, 2};
	sort(a.begin(), a.end(), std::greater<int>());
	for (auto &num : a) {
		cout << " sort: " << num << endl;
	}
}