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
/****************136只出现一次的数字***********************************/
//给定非空数组，只有一个元素出现一次，其他都出现两次
//寻找只出现一次的元素
/*******************哈希表***************************/
class Solution {
public:
	int singleNumber(vector<int>& nums) {
		unordered_map<int,int> nummap;
		int t = 0;
		for (int i = 0; i < nums.size(); i++) {
			nummap[nums[i]]++;//将所有元素以及出现的次数记录到哈希表中
		}
		int res = 0;
		for (auto& map : nummap) {
			if (map.second == 1)//遍历哈希表找到只出现一次的
				res = map.first;
		}

		return res;
		
	}
};
/*******************位运算***************************/
//元素与自身异或为0
//任何元素与0异或还是原来的数
//异或运算满足交换律和结合律
//因此将所有元素异或得到的结果就是只出现一次的元素
class Solution {
public:
	int singleNumber(vector<int>& nums) {
		int res = 0;
		for (auto e : nums) {
			res ^= e;
		}
		return res;

	}
};
int main()
{
	vector<int> arr{4,1,2,1,2};
	cout<<Solution().singleNumber(arr)<<endl;

	return 0;
}

