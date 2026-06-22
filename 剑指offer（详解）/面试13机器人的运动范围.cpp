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
// 面试题13:机器人的运动范围
// 题目：地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。
//一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下
//移动一格（不能移动到方格外），也不能进入行坐标和列坐标的数位之和
//大于k的格子。例如，当k为18时，机器人能够进入方格 [35, 37] ，
//因为3+5+3+7=18。但它不能进入方格 [35, 38]，因为3+5+3+8=19。
//请问该机器人能够到达多少个格子？
/********************递归*******************/
class Solution {
private:
	int row, col;
	int res;
	vector<vector<bool>> visited;
	bool isArea(int x, int y) {//边界判断
		return x >= 0 && x < row && y >= 0 && y < col;
	}
	bool access(int x, int y,int k) {//横纵坐标所有位的数字都加起来小于等于k
		int sum = 0;
		while (x != 0) {
			sum += x % 10;
			x /= 10;
		}
		while (y != 0) {
			sum += y % 10;
			y /= 10;
		}
		return sum <= k;
	}
	void findMax(int m, int n, int x, int y, int k) {
		if (!isArea(x,y)||visited[x][y]||!access(x, y, k))//超范围or访问过or不符合条件都返回
			return;
		visited[x][y] = true;
		res++;//一共可以到达多少个格子
		findMax(m, n, x + 1, y, k);//只需要向右下进行搜索
		findMax(m, n, x, y + 1, k);
	}
public:
	int movingCount(int m, int n, int k) {
		row = m;
		col = n;
		res = 0;
		if (k == 0)
			return 1;
		visited = vector<vector<bool>>(m, vector<bool>(n, false));
		findMax(m, n, 0, 0, k);
		return res;
	}
};
/********************动态规划*******************/
class Solution1 {
private:
	int row, col;
	int res;
	vector<vector<bool>> visited;
	bool isArea(int x, int y) {//边界判断
		return x >= 0 && x < row && y >= 0 && y < col;
	}
	bool access(int x, int y, int k) {//横纵坐标所有位的数字都加起来小于等于k
		int sum = 0;
		while (x != 0) {
			sum += x % 10;
			x /= 10;
		}
		while (y != 0) {
			sum += y % 10;
			y /= 10;
		}
		return sum <= k;
	}
public:
	int movingCount(int m, int n, int k) {
		if (k == 0)
			return 1;
		row = m;
		col = n;
		res = 0;
		visited = vector<vector<bool>>(m, vector<bool>(n, false));
		visited[0][0] = true;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (!isArea(i, j) || !access(i, j, k))
					continue;
				//visited[i][j]由visited[i-1][j]和visited[i][j-1]确定
				//只要有一个可到达就可以到达visited[i][j]
				if (i >= 1)
					visited[i][j]=visited[i][j] || visited[i - 1][j];
				if (j >= 1)
					visited[i][j] = visited[i][j] || visited[i][j-1];
				if (visited[i][j])
					res++;
			}
		}
		return res;
	}
};

int main()
{
	
	cout << Solution().movingCount(5, 4, 3)<<endl;
	return 0;
}

