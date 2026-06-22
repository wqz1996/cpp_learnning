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
using namespace std;
/************167两数之和-输入有序数组********************/
//给定升序排序的有序数组，找到两个数使得和等于目标数
//返回索引值
//不可以重复使用元素
class Solution {
public:
	vector<int> twoSum(vector<int>& numbers, int target) {
		vector<int> res;
		for (int i = 0; i < numbers.size(); i++) {
			int L = i+1;
			int R = numbers.size() - 1;
			while (L <= R) {
				int mid = L + (R - L) / 2;
				if (numbers[mid] == (target - numbers[i])) {
					res.push_back(i+1);
					res.push_back(mid+1);
				}
					
				if (numbers[mid] > target - numbers[i])
					R = mid - 1;
				else
					L = mid + 1;
			}
		}
		return res;
	}
	vector<int> twoSum1(vector<int>& numbers, int target) {
		assert(numbers.size() >= 2);
		vector<int> res;
		int p1 = 0;
		int p2 = numbers.size() - 1;
		while (p1 < p2) {
			if (numbers[p1] + numbers[p2] == target) {
				res.push_back(p1+1);
				res.push_back(p2+1);
				return res;
			}
			else if (numbers[p1] + numbers[p2] > target)
				p2--;
			else
				p1++;
				
		}
		throw invalid_argument("the input has no solution");

	}

};
int main() {
	int arr[] = { 2,7,11,15 };
	vector<int> v(arr, arr + sizeof(arr) / sizeof(int));//使用数组创建vector
	vector<int> vec{ 0,1,0,3,12 };
	int tag=9;
	vector<int> res = Solution().twoSum(v, tag);
	for (int i = 0; i < res.size(); i++) {
		cout << res[i] << " ";
	}
	cout << endl;

	return 0;
}