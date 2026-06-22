#include<vector>
#include<iostream>
using namespace std;
int main() {
	int n;
	while (cin >> n) {
		int count = n + 1;
		vector<int> v(count);
		for (int i = 0; i < n; i++) {
			v[i] = i;
		}
		while (count != 1) {
			int i = 0;
			for (; 2 * i + 1 < count; i++) {
				v[i] = v[2 * i + 1];
			}
			count = i;
		}
		cout << v[0] << endl;

	};
};