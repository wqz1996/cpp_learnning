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
/*************11盛最多水的容器*****************************/
/**************O(N^2)*****************/
//复杂样例无法通过
class Solution {
public:
	int maxArea(vector<int>& height) {
		int len = height.size();
		int maxV = 0;
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < len; j++) {
				maxV = max(maxV, abs(j - i) * min(height[i], height[j]));
			}
		}
		return maxV;
	}
};
/****************双指针***********************************/
//分别指向数组首尾
//保证两个尽可能大的数字距离尽可能远
class Solution {
public:
	int maxArea(vector<int>& height) {
		int len = height.size();
		int maxV = 0;
		int left = 0;//左指针
		int right = len - 1;//右指针
		while (left < right) {

			int tempV = (right - left) * min(height[left], height[right]);
			maxV = max(maxV, tempV);
			if (height[left] < height[right])//移动左右两侧数值较小的指针
				left++;
			else
				right--;
		}
		return maxV;
	}
};
int main()
{

	return 0;
}

