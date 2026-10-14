#include <iostream> // 使用处：第 33 行的 cin
//完全数（Perfect number），又称完美数或完备数，是一些特殊的自然数。
//它所有的真因子（即除了自身以外的约数）的和（即因子函数），恰好等于它本身。
//例如：28，它有约数1、2、4、7、14、28，除去它本身28外，其余5个数相加，1 + 2 + 4 + 7 + 14 = 28。
//给定函数count(int n), 用于计算n以内(含n)完全数的个数。计算范围, 0 < n <= 500000
//返回n以内完全数的个数。 异常情况返回 - 1
using namespace std;
bool perfectnum(int n) {//判断n是否是完全数
	int sum = 0;
	for (int i = 1; i < n ; i++) {
		if (n % i== 0) {
			sum += i;
			
		}
	}
	if (sum == n)
		return true;
	else
		return false;
		
}
int count(int n) {//统计从1-n的完全数个数
	int res = 0;
	for (int i = 1; i <= n; i++) {
		if (perfectnum(i))
			res++;
	}
	return res;
}
int main() {
	int n;

	while (cin >> n) {
		cout << count(n) << endl;
	}
	
	return 0;
}

