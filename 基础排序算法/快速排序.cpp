#include <cstdlib> // 使用处：第 32 行的 rand
#include <algorithm> // 使用处：第 10 行的 swap(
#include <vector> // 使用处：第 5 行的 vector
using namespace std;
vector<int> partition(vector<int>& arr, int L, int R) {
	int less = L - 1;//从L前一个开始作为less区域
	int more = R;//从最后一个元素作为more区域
	while (L < more) {//arr[R]为划分两个区域的参考数值
		if (arr[L] < arr[R])//arr[L]小于arr[R]
			swap(arr[++less], arr[L++]);//小于区域扩一位将L包括进来，L指向下一位
		else if (arr[L] > arr[R])//大于区域前一个与arr[L]交换，L不动继续比较
			swap(arr[--more], arr[L]);
		else//arr[L]==arr[R]
			L++;
	}
	swap(arr[more], arr[R]);//将最后的参考数值放入中间

	return vector<int>{less + 1, more};//返回等于区域的头尾索引

}
void quicksort(vector<int>& arr, int L, int R) {//经典快排
	if (L < R) {
		vector<int> p = partition(arr, L, R);
		//等于区域不用继续参与排序
		quicksort(arr, L, p[0] - 1);//递归排序小于区域部分
		quicksort(arr, p[1] + 1, R);//递归排序大于于区域部分
	}
}
void randomquicksort(vector<int>& arr, int L, int R) {//随机快排
	if (L < R) {
		//随机将末尾元素与中间的元素交换
		swap(arr[L + (int)(rand() / (RAND_MAX + 1)) * (R - L + 1)], arr[R]);
		vector<int> p = partition(arr, L, R);
		//等于区域不用继续参与排序
		randomquicksort(arr, L, p[0] - 1);//递归排序小于区域部分
		randomquicksort(arr, p[1] + 1, R);//递归排序大于于区域部分
	}	
}
int main()
{
	vector<int> arr{ 2,5,1,3,4 };
	randomquicksort(arr, 0, arr.size() - 1);
	
	return 0;
}

