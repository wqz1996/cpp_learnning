#include <algorithm> // 使用处：第 8 行的 swap(
#include <vector> // 使用处：第 4 行的 vector
using namespace std;
void bubblesort(vector<int>& arr) {//冒泡
	for (int i = 0; i < arr.size(); i++) {
		for (int j = i + 1; j < arr.size(); j++) {
			if (arr[j] < arr[i])
				swap(arr[i], arr[j]);
		}
	}
}
void selectsort(vector<int>& arr) {//选择
	int min;
	for (int i = 0; i < arr.size(); i++) {
		min = i;
		for (int j = i + 1; j < arr.size(); j++) {
			min = arr[j] < arr[min] ? j : min;//在i+1到末尾范围找到最小的元素
		}
		swap(arr[i], arr[min]);//与当前元素进行交换
	}
}
void insertsort(vector<int>& arr) { // 插入
	for (int i = 1; i < arr.size(); i++) {
		for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--)
			swap(arr[j], arr[j + 1]);
	}
}
int main()
{
	vector<int> arr{ 2,5,1,3,4 };
	bubblesort(arr);
	
	return 0;
}

