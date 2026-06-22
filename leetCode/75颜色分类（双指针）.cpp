#include<algorithm>//包含堆操作
#include<iostream>
#include<string>
#include<cmath>
#include<stack>//栈
#include<queue>//队列
#include<vector>//不注重插入和删除效率
#include<list>//类似双向链表，随即存取效率差，不支持[]符号，但是插入和删除效率高
#include<deque>//双端队列，兼顾随即存取，和两端数据的插入删除
#include<ctime>
#include< unordered_map>
#include< unordered_set>
#include<hash_map>
#include<hash_set>
#include<assert.h>
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