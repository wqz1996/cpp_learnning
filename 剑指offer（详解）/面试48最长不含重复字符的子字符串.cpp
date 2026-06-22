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
#include<set>
#include<map>
using namespace std;
//面试题48. 最长不含重复字符的子字符串
// 题目：请从字符串中找出一个最长的不包含重复字符的子字符串，
//计算该最长子字符串的长度。
class Solution {
private:
	bool ishas(string s,char target) {//s中是否包含target
		for (auto str : s) {
			if (str == target)
				return true;//包含返回true
		}
		return false;//不包含返回false
	}
public:
	int lengthOfLongestSubstring(string s) {
		if (s.empty())
			return 0;
		if (s.size() == 1)
			return 1;
		int len = s.size();
		int p1 = 0;
		int p2 = 1;
		int maxlen = 1;
		while (p2 != len) {
			if (ishas(s.substr(p1, p2-p1), s[p2])) {//包含target移动p1
				p1++;
				maxlen = max(maxlen, p2 - p1);
			}
			else {//不包含target移动p2判断下一位
				p2++;
				maxlen = max(maxlen, p2 - p1);
			}
				
		}
		return maxlen;
	}
};
/*****************使用哈希表优化滑动窗口************************/
class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		if (s.empty())
			return 0;
		int len = s.size();
		int p1 = 0;
		int p2 = 0;
		int maxlen = 1;
		unordered_map<char, int> m;
		while (p2 < len) {
			if (m.find(s[p2]) != m.end())//发现重复元素直接将p1移动到重复元素索引的下一位
				p1 = max(p1, m[s[p2]] + 1);
			m[s[p2++]] = p2;//记录每个字母出现的索引
			maxlen = max(p2 - p1, maxlen);
		}
		return maxlen;
	}
};


int main()
{
	string s = "pwwkew";
	Solution1().lengthOfLongestSubstring(s);

	return 0;
}

