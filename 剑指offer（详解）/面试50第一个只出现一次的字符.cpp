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
//面试题 50. 第一个只出现一次的字符
// 题目：在字符串 s 中找出第一个只出现一次的字符。
//如果没有，返回一个单空格。 s 只包含小写字母。
/***************哈希表************************/
class Solution {
public:
	char firstUniqChar(string s) {
		if (s.empty())
			return ' ';
		char res;
		unordered_map<char, int> strmap;
		for (int i = 0; i < s.size(); i++) 			
			strmap[s[i]]++;
		for (int i = 0; i < s.size(); i++) {
			if (strmap[s[i]] == 1)
				return s[i];
		}
		return ' ';
		
	}
};
class Solution {
public:
	char firstUniqChar(string s) {
		unordered_map<char, int> smap;
		for (char str : s) {
			smap[str]++;
		}
		for (char str : s) {
			if (smap[str] == 1)
				return str;
		}
		return ' ';
	}
};
int main()
{
	string s="abaccdeff";
	cout<<Solution().firstUniqChar(s);
	return 0;
}

