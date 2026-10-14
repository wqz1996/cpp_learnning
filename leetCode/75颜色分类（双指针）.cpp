#include <algorithm> // 使用处：第 25 行的 swap(
#include <iostream> // 使用处：第 55 行的 cout
#include <vector> // 使用处：第 11 行的 vector
#include <assert.h> // 使用处：第 14 行的 assert(
using namespace std;
/************75颜色分类*********************/
//给定有n个元素的数组，元素取值只有0，1，2三种可能
//给数组排序
class Solution {
public:
	void sortColors(vector<int>& nums) {
		int count[3] = { 0 };
		for (int i = 0; i < nums.size(); i++) {
			assert(nums[i] >= 0 && nums[i] <= 2);
			count[nums[i]]++;
		}
		int index = 0;
		for (int i = 0; i < (sizeof(count) / sizeof(int)); i++) {
			for (int j = 0; j < count[i]; j++) {
				nums[index++] = i;
			}
		}
		
	}
	void swap(vector<int>& nums, int i, int j) {
		int temp = nums[i];
		nums[i] = nums[j];
		nums[j] = temp;
	}
	void sortColors1(vector<int>& nums) {
		int zero = -1;
		int two = nums.size();
		int i = 0;
		while (i < two) {
			if (nums[i] == 1)
				i++;
			else if (nums[i] == 2) {
				swap(nums, i, --two);
			}
			else {
				assert(nums[i] == 0);
				swap(nums, ++zero, i++);
			}

		}

	}
};
int main() {
	int arr[] = { 0, 1, 2, 2, 1, 0, 2, 2 };
	vector<int> v(arr, arr + sizeof(arr) / sizeof(int));//使用数组创建vector
	vector<int> vec{ 0,1,0,3,12 };
	Solution().sortColors(v);
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;

	return 0;
}