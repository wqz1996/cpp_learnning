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
/****************22括号生成***********************************/
//给定n为括号的对数，生成所有可能的组合
/*******************剪枝回溯法***************************/
class Solution {
private:
	vector<string> res;
	void getthesis(string s, int left, int right) {
		if (left == 0 && right == 0) {
			res.push_back(s);
			return;
		}

		if (left > right)//要求左括号的剩余数量要小于右括号的剩余数量
			return;//即先放一个左括号才能再放一个右括号
		if(left>0)
		getthesis(s + "(", left - 1, right);//左括号还有剩余
		if(right>0)
		getthesis(s + ")", left, right-1);//右括号还有剩余
			
	}
public:
	vector<string> generateParenthesis(int n) {
		if (n == 0)//特判
			return res;

		getthesis("", n, n);//初始化字符串s为空，左右括号的数量都为n
		return res;
	
	}
};
int main()
{

	return 0;
}

