#include<algorithm>//包含堆操作
#include<iostream>
#include<sstream>//istringstream 可以将string以空格为分隔符分割
#include<string>
#include<cmath>
#include<stack>//栈
#include<queue>//队列
#include<vector>//不注重插入和删除效率
#include<list>//类似双向链表，随即存取效率差，不支持[]符号，但是插入和删除效率高
#include<deque>//双端队列，兼顾随即存取，和两端数据的插入删除
#include<ctime>
#include< unordered_map>
#include< unordered_set>
#include<hash_map>
#include<hash_set>
#include<assert.h>
#include<set>
#include<map>
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


