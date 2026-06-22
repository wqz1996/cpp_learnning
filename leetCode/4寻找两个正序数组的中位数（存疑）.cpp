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
/*************4寻找两个正序数组的中位数*****************************/
/**************时间复杂度O((M+N)****************************/
class Solution {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int len1 = nums1.size();
		int len2 = nums2.size();
		
		int midindex = (len1 + len2) / 2;
		vector<int> temp;
		temp.insert(temp.end(), nums1.begin(), nums1.end());
		temp.insert(temp.end(), nums2.begin(), nums2.end());
		sort(temp.begin(), temp.end());
		if ((len1 + len2) % 2) {
			return (double)temp[midindex];
		}
		else {
			return (double)(((double)temp[midindex] + (double)temp[midindex - 1])/2.0);
		}



	}
};
/*****************O(log(M+N))******************************/
class Solution {
private:
	double getMid(const vector<int>& nums1, const vector<int>& nums2, int k) {
		int len1 = nums1.size();
		int len2 = nums2.size();
		int index1 = 0, index2 = 0;
		while(1) {
			// 边界情况
			if (index1 == len1) {
				return nums2[index2 + k - 1];
			}
			if (index2 == len2) {
				return nums1[index1 + k - 1];
			}
			if (k == 1) {
				return min(nums1[index1], nums2[index2]);
			}

			// 正常情况
			int newIndex1 = min(index1 + k / 2 - 1, len1 - 1);
			int newIndex2 = min(index2 + k / 2 - 1, len2 - 1);
			int pivot1 = nums1[newIndex1];
			int pivot2 = nums2[newIndex2];
			if (pivot1 <= pivot2) {
				k -= newIndex1 - (index1 - 1);
				index1 = newIndex1 + 1;
			}
			else {
				k -= newIndex2 - (index2 - 1);
				index2 = newIndex2 + 1;
			}
		
		}
	}
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int len1 = nums1.size();
		int len2 = nums2.size();
		int totall = len1 + len2;
		if (totall % 2)
			return getMid(nums1, nums2, (totall / 2) + 1);
		else
			return (getMid(nums1, nums2, totall / 2) + getMid(nums1, nums2, totall / 2 + 1)) / 2.0;
		

	}
};
int main()
{
	vector<int> nums1{ 1,2 };
	vector<int> nums2{ 3,4 };
	cout<<Solution().findMedianSortedArrays(nums1, nums2)<<endl;
	return 0;
}

