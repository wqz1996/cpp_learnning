#include <iostream> // 使用处：第 47 行的 cout
using namespace std;
	//二分查找O(logN)
	int binarySearch(int arr[], int n, int target) {
		int L = 0;
		int R = n - 1;
		while (L <= R) {
			int mid = L + (R - L) / 2;//防止(L+R)/2整形溢出
			if (arr[mid] == target)
				return mid;
			if (arr[mid] > target)
				R = mid - 1;
			else
				L = mid + 1;
		}
		return -1;  

	}
	int binarySearchorder(int arr[], int L, int R, int target) {
		if (L > R)
			return -1;
		int mid = L + (R - L) / 2;
		if (arr[mid] == target)
			return mid;
		else if (arr[mid] > target)
			return binarySearchorder(arr, L, mid - 1, target);
		else
			return binarySearchorder(arr, mid + 1, R, target);
	}
int main() {

	//for (int i = 10; i <= 15; i++) {
	//	int n = pow(2, i);
	//	int* arr=Mytest().generateRandomArray(n, 0, 1000000000);
	//	/*int* arr = Mytest().genarateOrdererArray(n);*/
	//	clock_t starttime = clock();
	//	//Mytest().findMax(arr, n);
	//	Mytest().insertsort(arr, n);
	//	clock_t endtime = clock();
	//	cout << "data size 2^" << i << "=" << n << "\t";
	//	cout << "time cost:" << (double)(endtime - starttime) / CLOCKS_PER_SEC << endl;

	//	delete[] arr;
	//}
	int arr[] = {1,2,3,4,5,6 };
	int len = sizeof(arr) / sizeof(int);
	cout<<Mytest().binarySearchorder(arr, 0,len-1,5);

	//for (int i = 0; i < len; i++)
	//	cout << arr[i] << ' ';
	//cout << endl;


	return 0;
}
