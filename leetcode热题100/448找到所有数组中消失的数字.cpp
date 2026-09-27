#include <iostream> // cout、endl：main 输出两种解法
#include <vector> // vector：第 12 行首次使用
#include <cstdlib> // abs：第 38 行首次使用
using namespace std;
/**********************448找出所有数组中消失的数字*************************/
//给定一个范围在  1 ≤ a[i] ≤ n ( n = 数组大小 ) 的 整型数组，
//数组中的元素一些出现了两次，另一些只出现一次。
//找到所有在 [1, n] 范围之间没有出现在数组中的数字。
/*********************额外空间O(N)***********************/
class Solution {
public:
	vector<int> findDisappearedNumbers(vector<int>& nums) {
		int len = nums.size();
		vector<bool> board(len+1,false);//记录nums[i]是否出现过
		vector<int> res;
		if (len == 0)
			return res;
		for (int i = 0; i < len; i++) {
			board[nums[i]] = true;
		}
		for (int i = 1; i <= len; i++) {
			if (board[i] == false)//遍历寻找未出现的数字
				res.push_back(i);
		}
		return res;

	}
};
class Solution1 {
public:
	vector<int> findDisappearedNumbers(vector<int>& nums) {
	
		int len = nums.size();
		vector<int> res;
		if (len == 0)
			return res;
		for (int i = 0; i < len; i++) {
			if(nums[abs(nums[i]) - 1] > 0)//若该索引的数字未出现过
			nums[abs(nums[i]) - 1] = -nums[abs(nums[i]) - 1];//将该索引的元素标记为负
		}
		for (int i = 0; i < len; i++) {
			if (nums[i] > 0)//未标记过的则是未出现过的元素索引
				res.push_back(i + 1);
		}
		return res;

	}
};
int main()
{
    const vector<int> input{4, 3, 2, 7, 8, 2, 3, 1};
    vector<int> a = input, b = input;
    const auto first = Solution().findDisappearedNumbers(a);
    const auto second = Solution1().findDisappearedNumbers(b);
    for (const auto& result : {first, second}) {
        for (int value : result) cout << value << ' ';
        cout << endl;
    }
    return 0;
}
