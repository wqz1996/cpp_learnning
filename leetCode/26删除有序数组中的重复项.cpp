#include <vector> // 使用处：第 8 行的 vector
using namespace std;
/*************83删除排序链表中的重复元素*****************************/
//给你一个 非严格递增排列 的数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 
//返回删除后数组的新长度。元素的 相对顺序 应该保持 一致 。然后返回 nums 中唯一元素的个数。
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int slow = 0, fast = 0;
        while(fast<nums.size()){
            if(nums[slow] != nums[fast]){
                nums[++slow] = nums[fast];
            }
            fast++;
        }
        return slow+1;
    }
};
int main()
{

	return 0;
}

