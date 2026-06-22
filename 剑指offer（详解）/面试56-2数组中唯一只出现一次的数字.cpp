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
//面试题56 - II. 数组中数字出现的次数 II
// 题目：在一个数组 nums 中除一个数字只出现一次之外，其他数字都出现了三次。
//请找出那个只出现一次的数字。
/***********哈希表*************/
class Solution {
public:
	int singleNumber(vector<int>& nums) {
		unordered_map<int, int> nummap;
		for (int n : nums) {
			nummap[n]++;
		}
		int res;
		for (auto m : nummap) {
			if (m.second == 1) {
				res = m.first;
				break;
			}
				
		}
		return res;
	}
};
/***********位运算*************/
class Solution {
public:
	int singleNumber(vector<int>& nums) {
		int res = 0;
		for (int i = 0; i < 32; i++) {//分别判断32位每一位
			int cnt = 0;//记录当前位1的个数
			for (int n : nums) {
				if (n & (1 << i))//1<<i是1左移i位，和n进行与运算，统计第i位的1的个数
					cnt++;
			}
			if (cnt % 3 == 1)//第i位的1不能被3整除则将res该位置1
				res ^= (1 << i);
		}
		return res;
	}
}; 
int main()
{

	return 0;
}

