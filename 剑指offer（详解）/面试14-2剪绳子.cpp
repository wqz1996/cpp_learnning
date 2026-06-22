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
//面试题68 - II. 二叉树的最近公共祖先
// 给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m?段
//（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m - 1] 。
//请问 k[0]*k[1]*...*k[m - 1] 可能的最大乘积是多少？例如，当绳子的长度是8时，
//我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。
//答案需要取模 1e9 + 7（1000000007），如计算初始结果为：1000000008，请返回 1。
class Solution {
public:
	//n >= 5 2*(n-2) > n   3*(n-3) > n  且3*(n-3) >= 2*(n-2)
	//n = 4 2 * 2 > 1 * 3
	//2和3不能再分了  分了就变小了 且3优于2
	int cuttingRope(int n) {
		if (n <= 3) return n - 1;
		long rs = 1;
		while (n > 4) {
			//3最优
			rs *= 3;
			rs %= 1000000007;
			n -= 3;
		}
		//n = 1,2,3,4,5,6,7,8,9,10,11,12  减了n个3之后
		//n = 1,2,3,4,2,3,4,2,3,4, 2, 3
		//循环结束 只剩下1, 2 ,3,4   *1等于没有
		//2，3不能再分了
		//4 可以分成1 * 3  2 * 2,所以还是4最优
		//所以 剩下的1 2 3 4 都不能再分了
		return (rs * n) % 1000000007;
	}
};
int main()
{

	return 0;
}

