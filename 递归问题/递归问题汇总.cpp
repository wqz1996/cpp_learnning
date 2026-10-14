#include <algorithm> // 使用处：第 11 行的 max(
#include <iostream> // 使用处：第 18 行的 cout
using namespace std;
int getMax(int arr[], int L, int R) {//寻找数组中最大值：将数组分为左右，左边最大值和右边最大值的最大值即为全局最大值
	if (L == R) {
		return arr[L];
	}
	int mid = (L + R) / 2;
	int maxleft = getMax(arr, L, mid);
	int maxright = getMax(arr, mid + 1, R);
	return max(maxleft, maxright);

}
int main()
{
	int arr[5] = { 2, 5, 1, 3, 4 };
	int len = sizeof(arr) / sizeof(int);
	cout << getMax(arr, 0, len);

	return 0;


}