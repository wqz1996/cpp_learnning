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
/*************0-1背包问题******************/
class Knapsack01 {
private:
	vector<vector<int>> mem;//记忆化搜索
	//[0...index]的物品填充容积为C的背包的最大值
	/********************暴力递归************************/
	int bestvalue(const vector<int>& w, const vector<int>& v, int index, int c) {
		if (index < 0 || c <= 0)
			return 0;

		int res = bestvalue(w, v, index - 1, c);//不放入第index物品
		if (c >= w[index]) {
			res = max(res, v[index] + bestvalue(w, v, index - 1, c - w[index]));//放入第index物品
		}
		return res;
	}
	/********************记忆化搜索************************/
	int bestvalueMem(const vector<int>& w, const vector<int>& v, int index, int c) {

		if (index > w.size() - 1 || c <= 0)
			return 0;
		if (mem[index][c] != -1)
			return mem[index][c];
		int res = bestvalueMem(w, v, index + 1, c);//不考虑index
		if (c >= w[index]) {
			res = max(res, v[index] + bestvalueMem(w, v, index + 1, c - w[index]));//index-1从后向前，index+1从前向后都可以
		}
		mem[index][c] = res;
		return res;
	}


public:
	int knapsack01(const vector<int>& w, const vector<int>& v, int C) {
		assert(w.size() == v.size());
		int n = w.size();
		mem = vector<vector<int>>(n, vector<int>(C + 1, -1));//记忆化搜索记录已经完成的计算
		//return bestvalueMem(w, v, 0, C);//记忆化搜索
		return bestvalue(w, v, n - 1, C);//暴力递归

	}
	/********************动态规划************************/
	int knapsack01DP(const vector<int>& w, const vector<int>& v, int C) {
		assert(w.size() == v.size());
		int n = w.size();
		if (n == 0)
			return 0;
		vector<vector<int>> mem(n, vector<int>(C + 1, -1));
		for (int j = 0; j <= C; j++)
			mem[0][j] = (j >= w[0] ? v[0] : 0);
		for (int i = 1; i < n; i++) {
			for (int j = 0; j <= C; j++) {
				mem[i][j] = mem[i - 1][j];//不放第i个物品
				if (j >= w[i])
					mem[i][j] = max(mem[i][j], v[i] + mem[i - 1][j - w[i]]);//放第i个物品
			}
		}
		return mem[n - 1][C];

	}
	/*****************空间复杂度优化O(2*C)=O(C)****************************/
//每次动态规划只需要两行元素
	int knapsack01DPOP(const vector<int>& w, const vector<int>& v, int C) {
		assert(w.size() == v.size());
		int n = w.size();
		if (n == 0)
			return 0;
		vector<vector<int>> mem_op(2, vector<int>(C + 1, -1));//空间复杂度优化
		//第一行处理偶数行，第二行处理奇数行

		for (int j = 0; j <= C; j++)
			mem_op[0][j] = (j >= w[0] ? v[0] : 0);
		for (int i = 1; i < n; i++) {
			for (int j = 0; j <= C; j++) {
				//将mem_op中的行对2求模
				mem_op[i % 2][j] = mem_op[(i - 1) % 2][j];//不放第i个物品
				if (j >= w[i])
					mem_op[i % 2][j] = max(mem_op[i % 2][j], v[i] + mem_op[(i - 1) % 2][j - w[i]]);//放第i个物品
			}
		}
		return mem_op[(n - 1) % 2][C];

	}
	/*****************空间复杂度优化O(C)****************************/
//每次动态规划只需要一行元素
	int knapsack01DPOPOP(const vector<int>& w, const vector<int>& v, int C) {
		assert(w.size() == v.size());
		int n = w.size();
		if (n == 0)
			return 0;
		vector<int> mem_op(C + 1, -1);//一行元素从右向左更新
		//每个元素只需要考虑左边的值，因此先更新右侧
		for (int j = 0; j <= C; j++)
			mem_op[j] = (j >= w[0] ? v[0] : 0);
		for (int i = 1; i < n; i++) {
			for (int j = C; j >= w[i]; j--) {//从右侧开始更新
				//当j<w[i]时结束循环，不需要对mem_op[j]更新
				mem_op[j] = max(mem_op[j], v[i] + mem_op[j - w[i]]);
			}
		}
		return mem_op[C];

	}
};
int main()
{
	vector<int> v{ 6,10,12 };
	vector<int> w{ 1,2,3 };
	cout << Knapsack01().knapsack01DPOPOP(w, v, 5);

	return 0;
}

