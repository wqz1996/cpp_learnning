#include <string> // 使用处：第 36 行的 string
#include <vector> // 使用处：第 11 行的 vector
#include <unordered_map> // 使用处：第 12 行的 unordered_map
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