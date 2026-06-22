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
/************283 Move Zeros*********************/
//给定数组，将所有0移动到数组末尾，其他元素不变
class Solution {
public:
	void moveZeroes1(vector<int>& nums) {//基本方法 时间复杂度O(N),空间复杂度O(N)
		vector<int> temp;
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] != 0)
				temp.push_back(nums[i]);
		}
		for (int i = 0; i < temp.size(); i++) {
			nums[i] = temp[i];
		}
		for (int i = temp.size(); i < nums.size(); i++) {
			nums[i] = 0;
		}
	}
	void moveZeroes2(vector<int>& nums) {//不使用辅助空间 时间：O(N) 空间：O(1)
		int p=0;
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i])
				nums[p++] = nums[i];
		}
		for (int i = p; i < nums.size(); i++) {
			nums[i] = 0;
		}
	}
	void moveZeroes3(vector<int>& nums) {//非零元素和零元素交换
		int k = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] != 0) {
				if (i != k) {//避免自身交换
					int temp = nums[i];
					nums[i] = nums[k];
					nums[k++] = temp;
				}
				else
					k++;
				
			}
			
		}
			

	}
};
int main() {
	int arr[] = { 0,1,0,3,12 };
	vector<int> v(arr, arr + sizeof(arr) / sizeof(int));//使用数组创建vector
	vector<int> vec{ 0,1,0,3,12 };
	Solution().moveZeroes3(v);
	for (int i = 0; i < v.size(); i++) {
		cout << v[i]<<" ";
	}
	cout << endl;

	return 0;
}