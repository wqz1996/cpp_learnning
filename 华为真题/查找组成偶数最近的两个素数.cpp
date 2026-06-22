#include<iostream>
#include<vector>//不注重插入和删除效率
#include<assert.h>
using namespace std;
//输入n个整数，输出其中最小的k个。
bool judge(int n) {
	if (n < 2)
		return false;
	for (int i = 2; i < n; i++) {
		if (n % i == 0)
			return false;
	}
	return true;

}
//自写
int main() {

	int n;
	while (cin >> n) {
		assert(n % 2 == 0);
		assert(n > 2);
		vector<int> sushu;		
		for (int i = 2; i < n; i++) {
			if (judge(i))
				sushu.push_back(i);
		}
		int len = sushu.size();
		int p1 = 0;
		int p2 = sushu.size() - 1;
		vector<int> res = {0,0xffffff};
		while (p1 <= p2) {
			int sum = sushu[p1] + sushu[p2];
			if (sum > n) {
				p2--;
			}
			else if (sum < n) {
				p1++;
			}
			else {
				if (res[1] - res[0] > sushu[p2] - sushu[p1]) {
					res[0] = sushu[p1];
					res[1] = sushu[p2];
				}				
				p1++;
				p2--;
			}
		}
		for (int i = 0; i < 2; i++)
			cout << res[i] << endl;
	}
	return 0;
}
//简便方法
int main() {

	int n;
	while (cin >> n) {
		int half = n / 2;
		for (int i = 0; i < half; i++) {
			if (judge(half - i) && judge(half + i)) {
				cout << half - i << endl;
				cout << half + i << endl;
				break;
			}
		}

	}
	return 0;
}

