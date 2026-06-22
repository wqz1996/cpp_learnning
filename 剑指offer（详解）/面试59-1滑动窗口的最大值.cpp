#include<algorithm>//包含堆操作
#include<iostream>
#include<sstream>//istringstream 可以将string以空格为分隔符分割
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
//面试题59 - I. 滑动窗口的最大值
// 给定一个数组 nums 和滑动窗口的大小 k，请找出所有滑动窗口里的最大值。
/*************传统方法******************/
class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		vector<int> res;
		int p1 = 0;
		int p2 = k-1;
		while (p2 < nums.size()) {
			int maxvalue = INT_MIN;
			for (int i = p1; i <= p2; i++) {
				maxvalue = max(maxvalue, nums[i]);
			}
			res.push_back(maxvalue);
			p1++;
			p2++;
		}
		return res;
	}
};
/*************双端队列******************/
class Solution1 {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		vector<int> ans;   //定义一个数组保存结果
		deque<int> dq;    //定义一个双端队列来实现滑动窗口
		int n = nums.size();
		if (n == 0) return ans;		
		for (int i = 0; i < n; ++i) {
			while (!dq.empty() && nums[i] >= nums[dq.back()]) { //滑动窗口中只保存最大值，每次取时就是最大值了
				dq.pop_back();
			}
			while (!dq.empty() && dq.front() < i - k + 1) { //确实滑动窗口里的值是否有效，删除无效索引
				dq.pop_front();
			}
			dq.push_back(i);     //将原始数据逐步加入滑动窗口
			if (i >= k - 1) ans.push_back(nums[dq.front()]);   // 将每次的滑动窗口最大值存入我们的输出数组
		}
		return ans;

	}
};
//自己写的
class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		deque<int> qmax;//双端队列用于保存可能出现的最大值
		vector<int> res;//保存最后结果
		if (nums.empty())//空数组返回空
			return res;
		for (int i = 0; i < k; i++) {//先将0-k-1的可能出现的最大值放到qmax中
			while (!qmax.empty() && qmax.back() < nums[i])//维护一个降序序列，保存可能的最大值
				qmax.pop_back();
			qmax.push_back(nums[i]);
		}
		res.push_back(qmax.front());//qmax第一个就是第一个窗口可能的最大值
		int p1 = 0;//定义窗口开始和结束索引
		int p2 = k - 1;
		while (p2 < nums.size() - 1) {
			if (nums[p1] == qmax.front())//将要划出的元素是否是最大值，如果是最大值则要在qmax中弹出
				qmax.pop_front();
			p1++;//移动窗口
			p2++;
			while (!qmax.empty() && qmax.back() < nums[p2])//继续维护降序序列
				qmax.pop_back();
			qmax.push_back(nums[p2]);
			res.push_back(qmax.front());
		}
		return res;
	}
};
int main()
{
	vector<int> arr{ 1,3,-1,-3,5,3,6,7 };
	Solution1().maxSlidingWindow(arr, 3);
	return 0;
}

