#include <stdexcept> // 使用处：第 22 行的 invalid_argument
#include <string> // 使用处：第 32 行的 string
#include <vector> // 使用处：第 12 行的 vector
#include <unordered_map> // 使用处：第 13 行的 unordered_map
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