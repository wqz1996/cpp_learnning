#include <iostream> // 使用处：第 43 行的 cout
#include <string> // 使用处：第 11 行的 string
#include <unordered_map> // 使用处：第 15 行的 unordered_map
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

