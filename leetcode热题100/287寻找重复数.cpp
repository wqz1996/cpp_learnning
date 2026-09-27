#include <iostream> // cout、endl：main 输出两种解法
#include <vector> // vector：第 11 行首次使用
using namespace std;
/**********************287寻找重复数*************************/
// 给定一个包含 n + 1 个整数的数组 nums ，其数字都在 [1, n] 范围内（包括 1 和 n），可知至少存在一个重复的整数。
// 假设 nums 只有 一个重复的整数 ，返回 这个重复的数 。
// 你设计的解决方案必须 不修改 数组 nums 且只用常量级 O(1) 的额外空间
class Solution
{
public:
	int findDuplicate(vector<int> &nums)
	{
		int n = nums.size();
		int left = 1, right = n - 1, res = -1;
		while (left <= right)
		{
			int mid = left + (right - left) / 2;
			int cnt = 0;
			for (int &num : nums)
			{
				if (num <= mid)
					cnt++;
			}
			if (cnt <= mid)
			{
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
				res = mid;
			}
		}
		return res;
	}
};

class Solution1
{
public:
	//  利用环形链表的方法来判断
	// 将索引i以及nums[i]建立一个映射关系
	// 以数组[1,3,4,2]为例
	// i -> nums[i]
	// 0->1
	// 1->3
	// 2->4
	// 3->2
	// 从0开始查找nums[0] 再根据nums[0] 查找nums[nums[0]]以此类推 产生0->1->3->2->4->null 一个类似链表的结构
	int findDuplicate(vector<int> &nums)
	{
		int slow = 0;
		int fast = 0;
		slow = nums[slow];
		fast = nums[nums[fast]];
		while (slow != fast)
		{
			slow = nums[slow];
			fast = nums[nums[fast]];
		}		  // 先通过快慢指针，让两指针相遇
		fast = 0; // 将快指针回到头节点，让fast和slow都按照每次一步的速度继续运动，二者相遇时即为相交节点
		while (slow != fast)
		{
			slow = nums[slow];
			fast = nums[fast];
		}
		return slow;
	}
};
int main()
{
    vector<int> nums{1, 3, 4, 2, 2};
    cout << "二分计数: " << Solution().findDuplicate(nums) << endl;
    cout << "快慢指针: " << Solution1().findDuplicate(nums) << endl;
    return 0;
}
