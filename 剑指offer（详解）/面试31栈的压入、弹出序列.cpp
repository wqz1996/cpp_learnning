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
//面试题31. 栈的压入、弹出序列
// 题目：输入两个整数序列，第一个序列表示栈的压入顺序，
//请判断第二个序列是否为该栈的弹出顺序。假设压入栈的所
//有数字均不相等。例如，序列 {1,2,3,4,5} 是某栈的压栈序列，
//序列 {4,5,3,2,1} 是该压栈序列对应的一个弹出序列，但 {4,3,5,1,2} 
//就不可能是该压栈序列的弹出序列。
/***********最优解法模拟栈压入和弹出的过程***************/
class Solution1 {
public:
	bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
		stack<int> help;
		int j = 0;
		for (int i = 0; i < pushed.size(); i++) {
			help.push(pushed[i]);//压入pushed中的元素
			//直到help栈顶元素与popped[j]相等，弹出help栈顶，查找下一个popped元素
			while (!help.empty() && j < popped.size() && help.top() == popped[j]) {
				help.pop();
				j++;
			}
		}
		return help.empty();//若help栈中全部元素都可以弹出，则返回true
	}
};
class Solution {
public:
	bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
		vector<bool> isInStack(pushed.size(), false);
		stack<int> pushstack;
		for(int i=0;i<popped.size();i++){//弹出序列
			int j = 0;
			while (pushed[j] != popped[i])//找到压入序列中popped[i]的位置
				j++;
			for (int k = 0; k <= j; k++) {//将压入序列中popped[i]之前（包含），压入栈中
				if (!isInStack[k]) {//将未压入过的元素压入
					pushstack.push(pushed[k]);
					isInStack[k] = true;
				}				
			}
			if (!pushstack.empty()) {
				if (pushstack.top() == popped[i])//判断栈顶与弹出序列的元素能否对应
					pushstack.pop();
				else
					return false;
			}			
		}
		return true;
	}
};

class Solution {
public:
	bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
		stack<int> help;//栈中的序列
		queue<int> rest;//剩余未压入栈的序列
		for (int n : pushed)//按照先进先出进入队列
			rest.push(n);
		for (int n : popped) {
			if (rest.empty() && !help.empty() && help.top() != n)//rest为空且help栈顶与当前遍历的元素不等则返回false
				return false;
			while (!rest.empty() && (!help.empty() && help.top() != n) || help.empty()) {//help为空将剩余序列压入栈，或者help栈顶不等于当前遍历的元素且有剩余序列则将剩余序列压入栈
				help.push(rest.front());
				rest.pop();
			}
			if (!help.empty() && help.top() == n) {//栈顶元素等于当前遍历元素则弹出栈顶继续遍历下一个元素
				help.pop();
			}
		}
		return true;
	}
};
int main()
{
	vector<int> pushed = { 1,2,3,4,5 };
	vector<int> popped = { 4,3,5,1,2 };
	cout << Solution1().validateStackSequences(pushed, popped);
	return 0;
}

