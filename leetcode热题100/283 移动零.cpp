#include <iostream> // cout, endl：第 60 行首次使用
#include <vector> // vector：第 8 行首次使用
using namespace std;
/************283 Move Zeros*********************/
//给定数组，将所有0移动到数组末尾，其他元素不变
class Solution {
public:
	void moveZeroes1(vector<int>& nums) {//基本方法 时间复杂度O(N),空间复杂度O(N)
		vector<int> temp;
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] != 0)
				temp.push_back(nums[i]);
		}
		for (int i = 0; i < temp.size(); i++) {
			nums[i] = temp[i];
		}
		for (int i = temp.size(); i < nums.size(); i++) {
			nums[i] = 0;
		}
	}
	void moveZeroes2(vector<int>& nums) {//不使用辅助空间 时间：O(N) 空间：O(1)
		int p=0;
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i])
				nums[p++] = nums[i];
		}
		for (int i = p; i < nums.size(); i++) {
			nums[i] = 0;
		}
	}
	void moveZeroes3(vector<int>& nums) {//非零元素和零元素交换
		int k = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] != 0) {
				if (i != k) {//避免自身交换
					int temp = nums[i];
					nums[i] = nums[k];
					nums[k++] = temp;
				}
				else
					k++;
				
			}
			
		}
			

	}
};
int main()
{
    const vector<int> input{0, 1, 0, 3, 12};
    vector<int> a = input, b = input, c = input;
    Solution solution;
    solution.moveZeroes1(a);
    solution.moveZeroes2(b);
    solution.moveZeroes3(c);
    for (const auto& result : {a, b, c}) {
        for (int value : result) cout << value << ' ';
        cout << endl;
    }
    return 0;
}
