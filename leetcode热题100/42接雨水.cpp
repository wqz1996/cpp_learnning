#include <algorithm> // max：第 17 行首次使用
#include <vector> // vector：第 9 行首次使用
using namespace std;
/******************42接雨水*****************************/
// 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
// 双指针，找到i左边最大的，和右边最大的，两个最大的当中最小的与height[i]作差即为i位置能接的最多的雨水，遍历全部
class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty())
            return 0;
        int n = height.size();
        int left = 0, right = n - 1;
        int l_max = 0, r_max = 0;
        int res = 0;
        while (left < right) {
            l_max = max(l_max, height[left]);
            r_max = max(r_max, height[right]);
            if (l_max < r_max) {
                res += l_max - height[left++];

            } else {
                res += r_max - height[right--];
            }
        }
        return res;
    }
};
