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
// 面试题16:数值的整数次方
// 题目：实现函数double Power(double base, int exponent)，
//求base的exponent次方。不得使用库函数，同时不需要考虑大数问题。
/***************普通方法********************/
class Solution {
private:
	double powWithUnsiged(double x, int n) {
		double res = 1;
		for (int i = 0; i < n; i++)
			res *= x;
		return res;
	}
public:
	double myPow(double x, int n) {
		if (x == 0 && n < 0)//底数为0，指数为0是错误形式
			return 0;
		unsigned int absn = (unsigned int)n;
		if (n < 0)//指数小于0
			absn = (unsigned int)(-n);//先将指数取绝对值计算(-2^31,2^31-1)指数取反需要扩位
		double res = powWithUnsiged(x, absn);
		if (n < 0)//取倒数
			res = 1.0 / res;
		return res;
		
	}
};
class Solution1 {
private:
	double powWithUnsiged(double x, int n) {
		if (n == 0)//指数为0
			return 1;
		if (n == 1)//指数为1
			return x;
		double res = powWithUnsiged(x, n >> 1);//x^32=(x^16)*(x^16)
		res *= res;
		if ((n & 1) == 1)//判断奇数偶数
			res *= x;//奇数最后还得乘一个x
		return res;
	}
public:
	double myPow(double x, int n) {
		if (x == 0 && n < 0)//底数为0，指数为0是错误形式
			return 0;
		long absn = n;
		if (n < 0)//指数小于0
			absn = -absn;//先将指数取绝对值计算(-2^31,2^31-1)指数取反需要扩位
		double res = powWithUnsiged(x, absn);
		if (n < 0)//取倒数
			res = 1.0 / res;
		return res;

	}
};
/**************************优化程序******************************/
class Solution2 {
public:
	double myPow(double x, int n) {
		if (x == 0 && n < 0)//非法输入
			return 0;
		if (x == 1 || n == 0)//特例
			return 1;
		double res = 1;
		long num = n;//由于需要取负，因此需要扩大范围
		if (n < 0) {//底数取倒数
			num = -num;
			x = 1.0 / x;
		}
		while (num != 0) {
			if ((num & 1) != 0)//判断奇数偶数
				res *= x;//奇数时先乘一个x
			x *= x;//x*x...x^2*x^2...x^(n/2)*x^(n/2)
			num >>= 1;

		}
		return res;
	}
};
int main()
{

	cout<<Solution().myPow(2, 3)<<endl;
	return 0;
}

