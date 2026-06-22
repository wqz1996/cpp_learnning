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
// 面试题17:打印从1到最大的n位数
// 题目：输入数字 n，按顺序打印出从 1 到最大的 n 位十进制数。
//比如输入 3，则打印出 1、2、3 一直到最大的 3 位数 999。
/***************普通方法********************/
class Solution {
public:
	vector<int> printNumbers(int n) {
		vector<int> res;
		int num = 1;
		for (int i = 0; i < n; i++) {
			num *= 10;
		}
		for (int i = 1; i < num; i++) {
			res.push_back(i);
		}
		return res;
	}
};
/***************大数求解********************/
class Solution1 {
private:
	vector<int> res;
	bool increat(string& num) {//必须加引用符号修改num
		bool isOver = false;//判断是否越界
		int TakeOver = 0;
		int len = num.size();
		for (int i = len - 1; i >= 0; i--) {
			int nsum = num[i] - '0' + TakeOver;//计算当前位和进位的和
			if (i == len - 1)//在最低位加1
				nsum++;
			if (nsum >= 10) {
				if (i == 0)//最高位产生进位则越界
					isOver = true;
				else {//不是最高位则将低位数字归零，进位置1
					TakeOver = 1;
					num[i] = nsum - 10 + '0';
				}

			}
			else {//没有进位，则只设置当前位

				num[i] = nsum + '0';
				break;//设置完当前位不再继续设置更高位,防止将进位加到高位上
			}
				
		}
		return isOver;
	}
	void savenum(string num) {
		string s;
		auto it = num.find_first_not_of('0');//找到第一个而不是0的索引
		for (int i = it; i < num.size(); i++) {//将所有不是0的保存到s中
			s += num[i];
		}
		int nums = stoi(s);//将string转为int
		res.push_back(nums);
	}
public:
	vector<int> printNumbers(int n) {
		if (n <= 0)
			return res;
		string s(n,'0');//

		while (!increat(s)) {//循环修改并保存s的值，只要没越界继续循环

			savenum(s);//保存s的数值
		}
		return res;
		
	}
};
/***************递归（相当于全排列问题）********************/
class Solution2 {
private:
	vector<int> res;
	void savenum(string num) {
		string s;
		auto it = num.find_first_not_of('0');
		for (int i = it; i < num.size(); i++) {
			s += num[i];
		}
		if (s != "") {
			int nums = stoi(s);
			res.push_back(nums);
		}
	}
	void permutationnumbers(string& nums, int len, int index) {
		if (index == len) {//到最高位时
			savenum(nums);//保存现有结果
			return;
		}
		for (int i = 0; i < 10; i++) {//每一位都从0-9变化
			nums[index] = i + '0';
			permutationnumbers(nums, len, index + 1);//下一位的排列
		}
	}
public:
	vector<int> printNumbers(int n) {
		if (n <= 0)
			return res;
		string nums(n, '0');//初始化n位的字符串
		permutationnumbers(nums, n, 0);//递归排列每一位的数字
		return res;
	}
};
//自写
class Solution {
	vector<int> res;
	void savenum(string s) {
		int begin = s.find_first_not_of('0');//找到第一个不是0的开始数字
		if (begin != string::npos)//存在第一个不是0的数字
			s = s.substr(begin);
		else//若全是0则将s清空，不做保存
			s.clear();
		int num;
		if (!s.empty()) {
			num = stoi(s);
			res.push_back(num);
		}

	}
	void permuta(string& s, int index) {
		if (index == s.size()) {
			savenum(s);
			return;
		}
		for (int i = 0; i <= 9; i++) {
			s[index] = i + '0';//每一位数字都从0-9变化
			permuta(s, index + 1);
		}
	}
public:
	vector<int> printNumbers(int n) {
		if (n < 1)
			return res;
		string s(n, '0');
		permuta(s, 0);
		return res;
	}
};
int main()
{
	vector<int> ans = Solution2().printNumbers(1);
	return 0;
}

