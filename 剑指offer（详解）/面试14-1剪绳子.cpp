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
// 面试题13: 剪绳子1
// 题目：给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段
//（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m-1] 。
//请问 k[0]*k[1]*...*k[m-1] 可能的最大乘积是多少？
//例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，
//此时得到的最大乘积是18
/********************暴力递归*******************/
class Solution {
public:
	int cuttingRope(int n) {
		if (n == 2)//长度为2要求切一次则最大乘积为1
			return 1;
		int maxlen = -1;
		for (int i = 1; i <= n; i++) {//长度从1到n切割
			maxlen = max(maxlen,max(i * (n - i), i * cuttingRope(n - i)));//选择n-i是否继续切割
		}
		return maxlen;
	}
};
/********************记忆化搜索*******************/
class Solution1 {
private:
	vector<int> board;
	int FindMax(int n) {
		if (board[n] != 0)//保存计算过的值
			return board[n];
		int maxlen = -1;
		for (int i = 1; i <= n; i++) {//i<n或者i<=n都可以，因为i=n相当于没切
			maxlen = max(maxlen, max(i * (n - i), i * FindMax(n - i)));
		}
		board[n] = maxlen;
		return board[n];
	}
public:
	int cuttingRope(int n) {
		board = vector<int>(n+1,0);//board[0]没用记录从0-n一共n+1个数
		if (n == 2)
			return 1;
		return FindMax(n);
	}
};
/********************动态规划*******************/
class Solution2 {
public:
	int cuttingRope(int n) {
		vector<int> board(n + 1, 0);
		board[0] = 0;//没用
		board[1] = 1;//给定初始值
		board[2] = 1;
		int res = -1;
		for (int i = 3; i <= n; i++) {//从长度为3开始切割
			for (int j = 1; j <= i; j++) {//将长度为i的继续切割
				board[i] = max(board[i], max((i-j) * j, board[i - j] * j));//选择长度为j切割和没切割的乘积最大值
			}
		}
		return board[n];
	}
};
/********************贪心****************/
//将绳子尽可能的分成长度为3
class Solution3 {
public:
	int cuttingRope(int n) {
		if (n < 2)
			return 0;
		if (n == 2)
			return 1;
		if (n == 3)
			return 2;
		int cutlen3 = n / 3;//最多可以切长度为3的绳子的段数
		if (n - cutlen3 * 3 == 1)//最后一段剩下长度为4。3*1和2*2,应该选择2*2
			cutlen3 -= 1;//最后一段不剪成3和1，3的段数减1
		int cutlen2 = (n - cutlen3 * 3)/ 2;//n-cutlen3*3可能为1或2，为1时则最后一段就是2，不需要处理，为2时将最后一段长度为4切为2*2比1*3大
		return (int)pow(3, cutlen3) * (int)pow(2, cutlen2);//切为3的总乘积与切为2的总乘积

	}
};
/********************贪心****************/
//将绳子尽可能的分成长度为3
class Solution4 {
public:
	int cuttingRope(int n) {
		if (n < 4)
			return n - 1;
		int cut3 = n / 3;//裁成3的段数
		int rest = n % 3;//剩下的长度
		int res;
		if (rest == 0)
			res = (int)pow(3, cut3);//没有余数全部裁成长度为3
		if (rest == 1)
			res = (int)pow(3, cut3 - 1) * 4;//余数为1则将最后一个3和1组合为4，再裁成2*2=4>3*1=3
		if (rest == 2)
			res = (int)pow(3, cut3) * 2;//余数为2则最后一段是2不做处理
		return res;

	}
};
int main()
{
	cout << Solution1().cuttingRope(10) << endl;
	
	return 0;
}

