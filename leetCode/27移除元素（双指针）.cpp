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
/************27 移除元素*********************/
//给你一个数组 nums?和一个值 val，你需要 原地 移除所有数值等于?val?的元素，并返回移除后数组的新长度。
//不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。
//元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。


class Solution {
public:
	void swap(vector<int>& nums, int i, int j) {
		int temp = nums[i];
		nums[i] = nums[j];
		nums[j] = temp;
	}
	int removeElement(vector<int>& nums, int val) {
		int k = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] != val) {
				int temp = nums[i];
				nums[i] = nums[k];
				nums[k++] = temp;

			}


		}
		return k;

	}
};


class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if(nums.empty())
            return 0;
        int slow = 0, fast = 0;
        while(fast<nums.size()){
            if(nums[fast]!=val){
                nums[slow++] = nums[fast];
            }
            fast++;
            
        }
        return slow;
    }
};
int main() {
	int arr[] = { 0, 1, 2, 2, 3, 0, 4, 2 };
	vector<int> v(arr, arr + sizeof(arr) / sizeof(int));//使用数组创建vector
	vector<int> vec{ 0,1,0,3,12 };
	cout << Solution().removeElement(v, 2);
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;

	return 0;
}