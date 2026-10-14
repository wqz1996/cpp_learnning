#include <utility> // 使用处：第 16 行的 make_pair
#include <string> // 使用处：第 38 行的 string
#include <vector> // 使用处：第 11 行的 vector
#include <map> // 使用处：第 12 行的 map<
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