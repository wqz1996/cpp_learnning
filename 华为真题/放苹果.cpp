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
//把M个同样的苹果放在N个同样的盘子里，允许有的盘子空着不放，
//问共有多少种不同的分法？（用K表示）5，1，1和1，5，1 是同一种分法。
//f(m,n)=f(m-n,n)+f(m,n-1)
//f(m-n,n)->n个盘子都有苹果，转化成m-n个苹果放在n个盘子中的问题
//f(m,n-1)->有一个盘子是空的，则转化为m个苹果放在n-1个盘子中的问题
/****递归*******/
int count(int m, int n) {
	if (m < 0 || n < 0)
		return 0;
	else if (m == 1 || n == 1)
		return 1;
	else
		return count(m - n, n) + count(m, n - 1);
	
}
/****动态规划*******/
//dp[i][j]表示i个盘子放j个苹果问题
//dp[i][j]=dp[i-1][j]+(j-i<0?0:dp[i][j-i])
//i-1个盘子放j个苹果+苹果数量小于盘子数量则为0，否则i个盘子放j-i个苹果
int dpcount(int m, int n) {
	vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
	if (m == 1 || n == 1 || n == 0)
		return 1;
	for (int i = 0; i < m + 1; i++)
		dp[1][i] = 1;
	for (int i = 1; i < n + 1; i++)
		dp[i][0] = dp[i][1] = 1;
	for (int i = 2; i < n + 1; i++) {
		for (int j = 2; j < m + 1; j++) {
			dp[i][j] = dp[i - 1][j] + (j - i < 0 ? 0 : dp[i][j - i]);
		}
	}
	return dp[n][m];

}

int main() {
	int m, n;
	while (cin >> m >> n) {

		cout << dpcount(m, n) << endl;

	}
	return 0;
}
