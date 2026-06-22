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
#include<hash_map>
#include<hash_set>
#include<assert.h>
#include<set>
#include<map>
using namespace std;
//面试题60. n个骰子的点数
// 把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。
//输入n，打印出s的所有可能的值出现的概率。
//你需要用一个浮点数数组返回答案，其中第 i 个元素代表这 n 个骰子所能掷出的点数集合中第 i 小的那个的概率。
class Solution {
public:
	vector<double> twoSum(int n) {
		vector<double> res(6 * n + 1, 0);
		res[0] = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = 6 * i; j >= i; j--) {
				res[j] = 0;
				for (int x = j - 1; x >= i - 1 && x >= j - 6; x--) 
					res[j] += res[x];
			}
		}
		for (auto& num : res) 
			num /= pow(6, n);
		return vector<double>(res.begin() + n, res.end());
	}
};
//动态规划
class Solution {
public:
	vector<double> twoSum(int n) {
		vector<vector<int>> dp(n + 1, vector<int>(6 * n + 1));//dp[i][j] 前i个骰子凑成j的方法数量
		for (int i = 1; i <= 6; i++)//一个筛子凑成1-6的点数分别只有一种方法
			dp[1][i] = 1;
		for (int i = 2; i <= n; i++) {//从两个骰子开始
			for (int j = i; j <= 6 * n; j++) {//i个骰子凑成点数范围[n,6*n]
				for (int k = 1; k <= 6; k++) {//当前骰子可能的点数范围
					if (j <= k)//若凑成点数小于当前点数则跳出
						break;
					dp[i][j] += dp[i - 1][j - k];
				}
			}
		}
		int all = pow(6, n);//n个骰子可能出现的组合总数
		vector<double> res;
		for (int i = n; i <= 6 * n; i++)
			res.push_back((double)dp[n][i] / (double)all);
		return res;
	}
};
//压缩空间
class Solution {
public:
	vector<double> twoSum(int n) {
		vector<int> dp(6 * n + 1);
		for (int i = 1; i <= 6; i++) {//dp[i]只有一个骰子的可能点数的数目
			dp[i] = 1;
		}
		for (int i = 2; i <= n; i++) {
			for (int j = 6 * n; j >= i; j--) {//因为计算与左侧数据有关，因此从右侧开始更新
				dp[j] = 0;//初始化为0
				for (int k = 1; k <= 6; k++) {//当前骰子的点数范围
					if (j - k < i - 1)//当前j-k小于最小的组成范围，直接跳出
						break;
					dp[j] += dp[j - k];
				}
			}
		}
		int all = pow(6, n);//n个骰子可能出现的组合总数
		vector<double> res;
		for (int i = n; i <= 6 * n; i++)
			res.push_back((double)dp[i] / (double)all);
		return res;
	}
};
int main()
{

	return 0;
}

