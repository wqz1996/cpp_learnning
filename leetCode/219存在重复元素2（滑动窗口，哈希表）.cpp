#include <string> // 使用处：第 29 行的 string
#include <vector> // 使用处：第 10 行的 vector
#include <unordered_set> // 使用处：第 11 行的 unordered_set
using namespace std;
/************219存在重复元素2*******************/
//给定整数数组和整数k，判断数组中是否存在两个不同的索引i，j
//使得nums[i]==nums[j]并且i-j的绝对值不超多k
class Solution {
public:
	bool containsNearbyDuplicate(vector<int>& nums, int k) {
		unordered_set<int> record;
		for (int i = 0; i < nums.size(); i++) {
			if (record.find(nums[i]) != record.end())
				return true;
			record.insert(nums[i]);
			if (record.size() == k + 1)//保证滑动窗口长度为k
				record.erase(nums[i - k]);//删除窗口最左侧的值

		}
		return false;

	}
};
int main() {
	int arr1[] = { 2,7,3,5 };
	vector<int> v1(arr1, arr1 + sizeof(arr1) / sizeof(int));//使用数组创建vector
	int arr2[] = { 2,7,3,5 };
	vector<int> v2(arr2, arr2 + sizeof(arr2) / sizeof(int));//使用数组创建vector
	string s{ "abcabcbb" };
	int tag = 9;

	return 0;
} 