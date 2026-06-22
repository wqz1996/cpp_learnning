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
/************350两个数组的交集2********************/
//给定两个数组，计算交集
//注意：元素在两个数组中出现的次数一致
class Solution {
public:
	vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
		map<int, int> record;
		vector<int> res;
		for (int i = 0; i < nums1.size(); i++) {
			if (record.find(nums1[i]) == record.end())
				record.insert(make_pair(nums1[i], 1));
			else
				record[nums1[i]]++;
		}
		for (int i = 0; i < nums2.size(); i++) {
			if (record.find(nums2[i]) != record.end() && record[nums2[i]] > 0) {
				res.push_back(nums2[i]);
				record[nums2[i]]--;
				if (record[nums2[i]] == 0)
					record.erase(nums2[i]);
			}
		}
		return res;


	}
};
int main() {
	int arr1[] = { 2,7,3,5 };
	vector<int> v1(arr1, arr1 + sizeof(arr1) / sizeof(int));//使用数组创建vector
	int arr2[] = { 2,7,3,5 };
	vector<int> v2(arr2, arr2 + sizeof(arr2) / sizeof(int));//使用数组创建vector
	string s{ "abcabcbb" };
	vector<int> res = Solution().intersect(v1, v2);
	int tag = 9;

	return 0;
}