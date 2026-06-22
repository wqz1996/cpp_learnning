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
#include<set>
#include<map>
using namespace std;
/*************31下一个排列*****************************/
//实现获取下一个排列的函数，
//算法需要将给定数字序列重新排列成字典序中下一个更大的排列。
class Solution {
private:
	void swap(vector<int>& nums, int i, int j) {//交换元素
		int temp = nums[i];
		nums[i] = nums[j];
		nums[j] = temp;
	}
	void reverse(vector<int>& nums, int start) {//从start到末尾翻转顺序
		int i = start;
		int j = nums.size() - 1;
		while (i < j) {
			swap(nums, i, j);
			i++;
			j--;
		}
	}
public:
	void nextPermutation(vector<int>& nums) {
		int i = nums.size()-2;//从后面第二个元素开始找
		while (i >= 0 && nums[i + 1] <= nums[i])//找到一对相邻元素nums[i-1]<nums[i]
			i--;
		if (i >= 0) {
			int j = nums.size() - 1;
			while (j >=i+1 && nums[j] <= nums[i])//在[i+1...end]范围从后向前找到第一个大于nums[i]的
				j--;
			swap(nums, i, j);//交换nums[i]和nums[j]
		}
		//之前条件可以判断，i之后的元素为降序排列
		//为了得到下一个排序，需要将i之后的元素升序排列
		reverse(nums, i + 1);
		//若原数组已经是降序排列，则i<0，直接进行转化为升序即可
	}
};
int main()
{

	return 0;
}

