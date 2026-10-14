#include <vector> // 使用处：第 7 行的 vector
using namespace std;
// 给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
// 将其转化为0-1背包问题，将问题转化为求是否存在子集，使得子集相加为总和的一半
class Solution {
public:
    bool canPartition(vector<int>& nums) {
		int sum = 0;
        for(int& it:nums){
            sum+=it;
        }
        if(sum%2)
        	return false;
        int n = nums.size();
        int c = sum/2;
        vector<bool> dp(c+1,false);
        dp[0] = true;
        for(int i = 0; i < n; i++){
            for(int j = c; j>=nums[i]; j--){
                dp[j] = dp[j] || dp[j - nums[i]];
            }
        }
        return dp[c];
    }
};
int main()
{

	 
	return 0;
}


