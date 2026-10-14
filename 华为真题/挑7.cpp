#include <iostream> // 使用处：第 6 行的 cin
//输出7有关数字的个数，包括7的倍数，还有包含7的数字（如17，27，37...70，71，72，73...）的个数（一组测试用例里可能有多组数据，请注意处理）
using namespace std;
int main() {
	int n;
	while (cin >> n) {
		int res = 0;
		if (n < 7) {
			res = 0;
		}
		else {
			for (int i = 7; i <= n; i++) {
				if ((i % 7) == 0 || (i % 10) == 7 || (i % 100) / 10 == 7 || (i % 1000) / 100 == 7 || (i % 10000) / 1000 == 7)
					res++;
			}
		}
		cout << res << endl;
	}

	return 0;
}

