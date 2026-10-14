#include <climits> // 使用处：第 14 行的 INT_MAX
#include <algorithm> // 使用处：第 16 行的 min(
#include <vector> // 使用处：第 13 行的 vector
using namespace std;
// 面试题10：旋转数组的最小数字
// 题目：把一个数组最开始的若干个元素搬到数组的末尾，
//我们称之为数组的旋转。输入一个递增排序的数组的一个
//旋转，输出旋转数组的最小元素。
//例如，数组?[3,4,5,1,2] 为 [1,2,3,4,5] 的一个旋转，该数组的最小值为1
/************时间O(N)******************/
class Solution {
public:
	int minArray(vector<int>& numbers) {
		int minnum = INT_MAX;
		for (auto num : numbers) {
			minnum = min(minnum, num);
		}
		return minnum;
	}
};
/************时间O(logN)******************/
//二分法
class Solution {
public:
	int minArray(vector<int>& numbers) {
		int len = numbers.size();
		int p1 = 0;
		int p2 = len - 1;
		while (p1 < p2) {
			int mid = p1 - (p1 - p2) / 2;
			if (numbers[mid] > numbers[p2]) {//mid大于p2证明最小数在右侧
				p1 = mid + 1;

			}
			else if(numbers[mid]<numbers[p2]){//mid小于p2证明最小数在左侧
				p2 = mid;
			}
			else {//相等时将p2向左移动一位
				p2--;
			}
		}
		return numbers[p1];
	}
};
int main()
{
	
	return 0;
}

