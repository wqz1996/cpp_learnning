#include <vector> // 使用处：第 10 行的 vector
#include <unordered_map> // 使用处：第 11 行的 unordered_map
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

