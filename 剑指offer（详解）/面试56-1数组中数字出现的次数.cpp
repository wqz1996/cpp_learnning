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
//面试题56 - I. 数组中数字出现的次数
// 题目：一个整型数组 nums 里除两个数字之外，其他数字都出现了两次。
//请写程序找出这两个只出现一次的数字。要求时间复杂度是O(n)，空间复杂度是O(1)。
class Solution {
private:
	bool isbit1(int num, int index) {//判断右移index后最后一位是否为1
		num = num >> index;
		return (num & 1);
	}
public:
	vector<int> singleNumbers(vector<int>& nums) {
		int res = 0;
		for (auto e : nums) {//将所有元素进行异或运算得到res
			res ^= e;
		}
		int index = 0;
		while ((res & 1) == 0) {//判断右侧第一个1的位置
			res >>= 1;//找到第一个1的位置
			index++;
		}
		int num1 = 0, num2 = 0;
		//按照nums[i]从右到左index位是否是1分成两组，再分别将两组数据进行异或运算，得到了两个数字就是只出现一次的两个数字
		for (int i = 0; i < nums.size(); i++) {//两个只出现一次的数字被分到两个数组中
			if (isbit1(nums[i], index))//按照从右到左第index位是否为1分为两个数组进行异或运算
				num1 ^= nums[i];
			else
				num2 ^= nums[i];
		}
		return vector<int>{num1, num2};

	}
};
int main()
{
	vector<int> arr{ 1,2,5,2 };
	Solution().singleNumbers(arr);
	return 0;
}

