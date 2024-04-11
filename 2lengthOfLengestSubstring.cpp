#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        unordered_map<char, int> map;
        int left = 0;
        int res = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            if (map.find(s[i]) != map.end())
            {
                left = max(left, map[s[i]] + 1);
            }
            map[s[i]] = i;
            isdigit('1');
            int a = map['f'];
            res = max(res, i - left + 1);
        }
        return res;
    }
};

int main() {
    Solution s;
    std::cout << s.lengthOfLongestSubstring("abcbbc") << endl;
}