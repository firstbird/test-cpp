#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Solution {
public:
// 3 2 4 1
    vector<int> pancakeSort(vector<int>& arr) {
        vector<int> res;
        int n = arr.size();
        for (size_t i = n - 1; i > 0; i--)
        {
            int maxIndex = findMax(arr, i);
            //int maxIndex = max_element(arr.begin(), arr.begin() + i + 1) - arr.begin();
            //int max = arr[maxIndex];
            if (maxIndex != -1) {
                reverse(arr.begin(), arr.begin() + maxIndex + 1);
                res.push_back(maxIndex + 1);
            }
            reverse(arr.begin(), arr.begin() + i + 1);
            res.push_back(i + 1);
        }        
        return res;
    }

private:
    int findMax(vector<int>& arr, int end){
        int max = INT_MIN;
        int maxIndex = -1;
        for (size_t i = 0; i <= end; i++)
        {
            if (arr[i] > max) {
                max = arr[i];
                maxIndex = i;
            }
        }
        return maxIndex;
    }   
};

int main() {
    class Solution so;
    vector<int> input = {3, 2, 4, 1};
    so.pancakeSort(input);
    for (auto i : input) {
        cout<<i;
    }
    return 0;
}