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
/************349两个数组的交集********************/
//给定两个数组，计算交集
//注意：结果中相同元素只出现一次，顺序可以任意
class Solution {
public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		set<int> record;
		//set<int> record(nums1.begin(), nums1.end());//直接利用容器构造
		set<int> res;
		vector<int> resvector;
		for (int i = 0; i < nums1.size(); i++) {
			record.insert(nums1[i]);//自动去重复
		}
		//
		for (int i = 0; i < nums2.size(); i++) {
			if (record.find(nums2[i]) != record.end()) {
				res.insert(nums2[i]);
			}
		}
		for (set<int>::iterator it = res.begin(); it != res.end(); it++) {
			resvector.push_back(*it);
		}

		//vector<int> resvector(res.begin(),res.end());//代替上述循环
		return resvector;
	}
};
int main() {
	int arr[] = { 2,7,3,5 };
	vector<int> v(arr, arr + sizeof(arr) / sizeof(int));//使用数组创建vector
	string s{ "abcabcbb" };
	vector<int> res=Solution().intersection();
	int tag = 9;

	return 0;
}