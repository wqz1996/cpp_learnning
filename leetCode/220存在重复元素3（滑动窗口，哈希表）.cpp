#include <string> // 使用处：第 27 行的 string
#include <vector> // 使用处：第 8 行的 vector
#include <set> // 使用处：第 9 行的 set<
using namespace std;
/************220存在重复元素3*******************/
class Solution {
public:
	bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
		set<long long> record;//加法操作避免超过32位整形的边界
		for (int i = 0; i < nums.size(); i++) {
			if (record.lower_bound((long long)nums[i] - (long long)t) != record.end()&&//找到v-t
				*record.lower_bound((long long)nums[i] - (long long)t)<= (long long)nums[i]+ (long long)t) {//取值小于v+t
				return true;
			}
			record.insert(nums[i]);
			if (record.size() == k + 1)
				record.erase(nums[i - k]);
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