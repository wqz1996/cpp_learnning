#include<algorithm>//包含堆操作
#include<iostream>
#include<sstream>//istringstream 可以将string以空格为分隔符分割
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
#include<assert.h>
#include<set>
#include<map>
using namespace std;

//KMP算法，两个字符串s1,s2，返回s2在s1中的开始位置，若s1不包含s2返回-1
class Solution {
private:
	vector<int> getNextArray(string s2) {//求解s2每个字符位置之前的最长相等前缀后缀的长度
		if (s2.size() == 1)//s2只有一个字符，因为前面没有字符，规定为-1
			return vector<int>{-1};
		vector<int> next(s2.size());
		next[0] = -1;
		next[1] = 0;//第二个字符前面只有一个字符，前缀后缀要求不能相同，因此为0
		int i = 2;//从第三个字符开始计算
		int cn = 0;//记录前缀后一个字符的最长相等前缀后缀的长度
		while (i < next.size()) {
			if (s2[i - 1] == s2[cn]) {//第i个字符的结果是，判断i-1字符与cn位置的字符是否相等，相等则next[i]是cn+1
				next[i++] = ++cn;
			}
			else if (cn > 0)//
				cn = next[cn];//cn跳到s2[cn]位置，进行上一步的判断
			else
				next[i++] = 0;//cn=0即已经跳到第一个字符位置，则第i个字符的next数值为0
		}
		return next;
	}
public:
	int getindexof(string s1, string s2) {
		if (s1.empty() || s2.empty() || s1.size() < s2.size())
			return -1;
		int i1 = 0;//s1的指针
		int i2 = 0;//s2的指针
		vector<int> next = getNextArray(s2);//求解s2的next数组
		while (i1 < s1.size() && i2 < s2.size()) {
			if (s1[i1] == s2[i2]) {//当前位置相等则两个指针都向后移动，直至找到不等的位置
				i1++;
				i2++;
			}
			else if (next[i2] == -1)//如果s2[i2]位置next数值为-1，说明已经匹配到第一个字符都不想等，则i1指针向后移动，重新进行上一步比较
				i1++;
			else
				i2 = next[i2];//将i2跳到最长前缀的后一个字符与s1[i1]进行比较
		}
		return i2 == s2.size() ? i1 - i2 : -1;//若s2所有的字符都匹配完成则返回i1-i2即可，否则s1不包含s2

	}
};

int main() {

	string s1 = "ababca";
	string s2 = "abc";
	int res =	Solution().getindexof(s1, s2);
	cout << res << endl;
	return 0;
}
