#include<algorithm>//包含堆操作
#include<iostream>
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
