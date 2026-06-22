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
/************454四数相加2********************/
//给定四个整数数组A,B,C,D计算有多少个元组，使得
//A[i]+B[j]+C[k]+D[l]=0
//注意：四个数组具有相同长度N，0<=N<=500
class Solution {
public:
	int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
		unordered_map<int, int> record;//
		for (int i = 0; i < C.size(); i++) {
			for (int j = 0; j < D.size(); j++) {
				record[C[i] + D[j]]++;
			}
		}
		int res = 0;
		for (int i = 0; i < A.size(); i++) {
			for (int j = 0; j < B.size(); j++) {
				if (record.find(0-A[i] - B[j]) != record.end()) {
					res += record[0 - A[i] - B[j]];
				}
			}
		}
		return res;

	}
	
};
int main() {
	int arr1[] = { 2,7,3,5 };
	vector<int> v1(arr1, arr1 + sizeof(arr1) / sizeof(int));//使用数组创建vector
	int arr2[] = { 2,7,3,5 };
	vector<int> v2(arr2, arr2 + sizeof(arr2) / sizeof(int));//使用数组创建vector
	string s{ "abcabcbb" };
	vector<int> res = Solution().twoSum(v1, v2);
	int tag = 9;

	return 0;
} 