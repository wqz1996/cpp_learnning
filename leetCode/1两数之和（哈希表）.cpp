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
/************1两数之和********************/
//给定整数数组nums和目标值target
//找出和为目标值两个元素的索引
//注意：有唯一解，每个元素用一次
class Solution { 
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int, int> record;
		for (int i = 0; i < nums.size(); i++) {
			int comlement = target - nums[i];
			if (record.find(comlement) != record.end()) {
				int res[2] = { i,record[comlement] };
				return vector<int>(res, res + 2);
			}
			record[nums[i]] = i;
		}
		throw invalid_argument("The input has no solution!");
		

	}
};
int main() {
	int arr1[] = { 2,7,3,5 };
	vector<int> v1(arr1, arr1 + sizeof(arr1) / sizeof(int));//使用数组创建vector
	int arr2[] = { 2,7,3,5 };
	vector<int> v2(arr2, arr2 + sizeof(arr2) / sizeof(int));//使用数组创建vector
	string s{ "abcabcbb" };
	vector<int> res = Solution().twoSum(v1, v2);
	int tag = 9;

	return 0;
} 