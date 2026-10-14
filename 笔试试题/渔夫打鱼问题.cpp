#include <iostream> // 使用处：第 26 行的 cin
using namespace std;
int res;
int findmethor(int n, int k,int index,int rest) {
	if (index == 2 * n + 1) {
		if (rest == 0)
			res++;
		return rest;
	}
	if(index==1)
		rest = findmethor(n, k, index + 1, rest + 1);
	else if (index != k) {
		rest = findmethor(n, k, index + 1,rest + 1);
		rest = findmethor(n, k, index + 1, rest - 1);
	}
	else if(index==k){
		rest = findmethor(n, k, index + 1, rest - 1);
	}
	return rest;

}
int main()
{

	int n, k;
	while (cin >> n >> k) {
		res = 0;
		findmethor(n,k,1,0);
		cout << res << endl;
	}

	return 0;
}
