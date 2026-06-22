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
/*************15三数之和*****************************/
//给定数组nums，找出三个元素和为0，输出不重复的所有结果
class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		int len = nums.size();
		vector<vector<int>> res;
		vector<int> tmp;
		if (len < 3||nums.empty())//数组元素小于3个返回空数组数组为空返回空数组	
			return res;
		
	
		sort(nums.begin(), nums.end());//升序排序

		for (int i = 0; i < len; i++) {
			if (nums[i] > 0)//当第一个数字已经大于0，有序数组升序，因此后面不可能成立
				break;
			if (i > 0 && nums[i] == nums[i - 1])//去第一个数字的重复
				continue;
			int left = i + 1;
			int right = len - 1;
			while (left < right) {
				int sum = nums[i] + nums[left] + nums[right];
				if (sum > 0) {//和大于零右指针左移
					right--;
				}
				else if (sum < 0) {//和小于零左指针右移
					left++;
				}
				else {
					assert(sum==0);
					tmp = { nums[i],nums[left],nums[right] };
					res.emplace_back(tmp);
					while (left < right && nums[left] == nums[left + 1])//指针不对撞时，去掉重复元素
						left++;
					while (left < right && nums[right] == nums[right - 1])
						right--;
					left++;//判断下一组数据是否符合条件
					right--;
				}
			}
			
		}
		return res;
	}
};

int main()
{

	return 0;
}

