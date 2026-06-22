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
/*************5最长回文子串*****************************/
//给定子串，返回最长的回文子串
//注：一个元素也叫回文
/***********************动态规划**************************/
class Solution {
public:
	string longestPalindrome(string s) {
		int n = s.size();
		if (n < 2)//长度小于2必然是回文结构，返回s本身
			return s;
		int maxlen = 1;//最长回文长度
		int begin = 0;//最长回文起始位置
		vector<vector<bool>> dp(n, vector<bool>(n, false));//动态规划表，行表示首字符位置，列表示尾字符位置,bool信息表示从[i..j]是否为回文结构
		for (int i = 0; i < n; i++)//一个元素必然是回文，初始状态
			dp[i][i] = true;
		for (int j = 1; j < n; j++) {//列循环
			for (int i = 0; i < j; i++) {//行循环
				if (s[i] != s[j])//收尾两个元素不相等则[i..j]不是回文
					dp[i][j] = false;
				else {//首尾相等
					if (j - i < 3)//j-1-(i+1)+1<2->dp[i+1][j-1]元素个数小于2
						dp[i][j] = true;//去掉首尾元素后长度小于2则一定是回文
					else
						dp[i][j] = dp[i + 1][j - 1];//否则取决于去掉首尾后的子串信息

				}
				if (dp[i][j] == true && j - i + 1 > maxlen) {
					maxlen = j - i + 1;
					begin = i;
				}

			}
		}
		return s.substr(begin,maxlen);//string中从begin开始的maxlen个元素
	
	}

};
/**********************中心扩散法*************************/
class Solution {
private:
	int* expandAroundCenter(const string& s, int left, int right) {
		while (left >= 0 && right < s.size() && s[left] == s[right]) {//首尾相等并且未到边界左右分别向外扩一个元素
			left--;
			right++;
		}
		return new int[2]{ left + 1,right - 1 };//返回首尾索引
	}
public:
	string longestPalindrome(string s) {
		if (s.size() < 2)
			return s;
		int start = 0, end = 0;
		for (int i = 0; i < s.size(); i++) {
			int* range1 = expandAroundCenter(s, i, i);//奇数情况
			int* range2 = expandAroundCenter(s, i, i+1);//偶数情况
			if ((*(range1 + 1) - *range1) > end - start) {//更新，保存最长的子串
				end = *(range1 + 1);//右边界
				start = *(range1);//左边界
			}
			if ((*(range2 + 1) - *range2) > end - start) {
				end = *(range2 + 1);
				start = *(range2);
			}
			
		}
		return s.substr(start, end - start + 1);
	}

};
int main()
{
	
	return 0;
}

