class Solution {
private:
	int findrob(vector<int> nums, int start, int end) {
		int dp_i_1 = 0, dp_i_2 = 0, dp_i = 0;
		for (int i = end; i >= start; i--) {
			dp_i = max(dp_i_1, nums[i] + dp_i_2);
			dp_i_2 = dp_i_1;
			dp_i_1 = dp_i;
		}
		return dp_i;
	}
public:
	int rob(vector<int>& nums) {
		if (nums.empty())
			return 0;
		int n = nums.size();
		if (n == 1)
			return nums[0];
		return max(findrob(nums, 0, n - 2), findrob(nums, 1, n - 1));//因为头尾不能同时抢，将其分为两种情况，[0,n-2]和[1,n-1]
	}
};