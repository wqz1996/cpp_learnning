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
//面试题45. 把数组排成最小的数
// 题目：输入一个非负整数数组，把数组里所有数字拼接起来排成一个数，
//打印能拼接出的所有数字中最小的一个。。
bool compare(const int& num1, const int& num2) {//比较器
	string s1 = to_string(num1);
	string s2 = to_string(num2);
	string combine1 = s1 + s2;//s1s2组合
	string combine2 = s2 + s1;//s2s1组合
	return combine1 < combine2;//升序排列
}
class Solution {
public:
	string minNumber(vector<int>& nums) {
		string res;
		sort(nums.begin(), nums.end(), compare);//使用比较器进行排列
		for (int i = 0; i < nums.size(); i++) {//将排序后的数组转化为string
			res += to_string(nums[i]);
		}
		return res;
	}
};
class Solution {
public:
	string minNumber(vector<int>& nums) {
		vector<string>strs;
		string ans;
		for (int i = 0; i < nums.size(); i++) {
			strs.push_back(to_string(nums[i]));
		}
		sort(strs.begin(), strs.end(), [](string& s1, string& s2) {return s1 + s2 < s2 + s1; });//lambda表达式重新定义排序规则
		for (int i = 0; i < strs.size(); i++)
			ans += strs[i];
		return ans;
	}
};

int main()
{
	vector<int> nums{ 3,30,34,5,9 };

	return 0;
}

