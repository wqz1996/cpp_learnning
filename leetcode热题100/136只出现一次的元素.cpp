#include <iostream> // cout, endl：第 46 行首次使用
#include <vector> // vector：第 11 行首次使用
#include <unordered_map> // unordered_map：第 12 行首次使用
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

