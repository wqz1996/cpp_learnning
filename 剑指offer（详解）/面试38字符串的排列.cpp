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
//面试题38. 字符串的排列
// 题目：输入一个字符串，打印出该字符串中字符的所有排列。
/****************递归搜索************************/
class Solution {
private:
	vector<string> res;//记录最终结果
	vector<bool> isused;//记录对应是否使用过
	string temp;//记录当前的结果
	void premute(string s, int index) {

		if (index == s.size()) {//到最后一个字母
			res.push_back(temp);//记录一个结果
			return;

		}
		for (int i = 0; i < s.size(); i++) {
			if (i > 0 && !isused[i - 1] && s[i - 1] == s[i])//去除重复元素
				continue;
			if (!isused[i]) {//当前字母未使用过
				temp += s[i];//加到后面
				isused[i] = true;//当前字母标记为使用过
				premute(s, index + 1);//递归放置下一个字母
				temp.pop_back();//回溯
				isused[i] = false;
			}

		}
	}
public:
	vector<string> permutation(string s) {
		if (s.empty())
			return res;
		sort(s.begin(), s.end());
		isused = vector<bool>(s.size(), false);//记录字母是否使用过
		premute(s, 0);//递归过程
		return res;

	}
};
class Solution {
private:
	vector<string> res;
	vector<bool> used;
	unordered_set<string> m;//记录用于去重
	string temp;
	void permute(string s, int index) {
		if (index == s.size()) {
			if (m.find(temp) == m.end()) {
				res.push_back(temp);
				m.insert(temp);
			}
			return;
		}
		for (int i = 0; i < s.size(); i++) {
			if (!used[i]) {
				used[i] = true;
				temp += s[i];
				permute(s, index + 1);
				used[i] = false;
				temp.pop_back();
			}
		}

	}
public:
	vector<string> permutation(string s) {
		int len = s.size();
		if (s.empty())
			return res;
		used = vector<bool>(len, false);
		sort(s.begin(), s.end());
		permute(s, 0);
		return res;
	}
};
int main()
{
	string s = "aab";
	Solution().permutation(s);

	return 0;
}

