#include<algorithm>//包含堆操作
#include<iostream>
#include<string>
#include<cmath>
#include<stack>//栈
#include<queue>//队列
#include<vector>//不注重插入和删除效率
#include<list>//类似双向链表，随即存取效率差，不支持[]符号，但是插入和删除效率高
#include<deque>//双端队列，兼顾随即存取，和两端数据的插入删除
#include<ctime>
#include< unordered_map>
#include< unordered_set>
#include<hash_map>
#include<hash_set>
#include<assert.h>
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