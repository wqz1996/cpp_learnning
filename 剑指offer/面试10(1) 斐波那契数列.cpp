using namespace std;
// 面试题10：斐波那契数列
// 题目：写一个函数，输入n，求斐波那契（Fibonacci）数列的第n项。
class Solution {
public:
	int Fibonacci(int n) {
		int begin[2] = { 0,1 };
		if (n < 2)
			return begin[n];
		long fibfirst = 0;
		long fibsecond = 1;
		int fibn = 0;
		for (int i = 2; i <= n; i++) {
			fibn = fibfirst + fibsecond;
			fibfirst = fibsecond;
			fibsecond = fibn;
		}
		return fibn;
	}
};
/*******************递归***************/
int Fibn(int n) {
	if (n <= 0)
		return 0;
	if (n == 1)
		return 1;
	return Fibn(n - 1) + Fibn(n - 2);
}
int main()
{

	return 0;

}



