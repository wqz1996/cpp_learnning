#include <functional> // 使用处：第 11 行的 greater<
#include <iostream> // 使用处：第 10 行的 cin
#include <queue> // 使用处：第 11 行的 priority_queue
#include <vector> // 使用处：第 11 行的 vector
using namespace std;
//输入n个整数，输出其中最小的k个。
int main() {
	int n,k;

	while (cin >> n >> k) {
		priority_queue<int,vector<int>,greater<>> q;
		int temp;
		for (int i = 0; i < n; i++) {
			cin >> temp;
			q.push(temp);
		}
		for (int i = 0; i < k; i++) {
			int res = q.top();
			q.pop();
			cout << res <<' ';
		}
		cout << endl;
	}
	
	return 0;
}

