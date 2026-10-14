#include <algorithm> // 使用处：第 25 行的 max(
#include <iostream> // 使用处：第 35 行的 cout
#include <string> // 使用处：第 11 行的 string
#include <vector> // 使用处：第 33 行的 vector
using namespace std;
/************3无重复字符串的最长子串********************/
//给定字符串，找出不包含重复在字符的最长子串长度
//注意：大小写？字母+数字？
class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		int L = 0;
		int R = -1;
		int freq[256] = { 0 };//记录所有字符的出现频率
		int res = 0;
		while (L < s.size()) {
			if (R + 1 < s.size() && freq[s[R + 1]] == 0) {
				R++;
				freq[s[R]]++;
			}
			else {
				freq[s[L]]--;
				L++;
			}
			res = max(res, R - L + 1);
		}
		return res;

	}
};
int main() {
	int arr[] = { 2,7,3,5 };
	vector<int> v(arr, arr + sizeof(arr) / sizeof(int));//使用数组创建vector
	string s{ "abcabcbb" };
	cout << Solution().lengthOfLongestSubstring(s);
	int tag = 9;

	return 0;
}