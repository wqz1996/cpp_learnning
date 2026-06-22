#include<iostream>
using namespace std;
bool judge(int num) {
	if (num < 2)
		return false;
	for (int i = num - 1; i >= 2; i--)
		if (num % i == 0)
			return false;
	return true;
}
int main()
{
	int a;
	while (cin>>a) {
		cout << judge(a);
	}

	return 0;
}
