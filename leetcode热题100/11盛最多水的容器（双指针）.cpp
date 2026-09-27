#include <algorithm> // max, min：第 15 行首次使用
#include <vector> // vector：第 10 行首次使用
#include <cstdlib> // abs：第 15 行首次使用
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

