#include <vector> // 使用处：第 11 行的 vector
using namespace std;
//面试题66. 构建乘积数组
// 给定一个数组 A[0,1,…,n-1]，请构建一个数组 B[0,1,…,n-1]，其中 B 中的元
//素 B[i]=A[0]×A[1]×…×A[i-1]×A[i+1]×…×A[n-1]。不能使用除法。
//使用矩阵进行构建，C[i]=A[0]*A[1]*...*A[i-1],D[i]=A[i+1]*...*A[n-1]
//C[i]=C[i-1]*A[i-1],D[i]=D[i-1]*A[i+1]
//B[i]=C[i]*D[i]
class Solution {
public:
	vector<int> constructArr(vector<int>& a) {
		int n = a.size();
		vector<int> res(n,1);
		int left = 1;
		for (int i = 0; i < n; i++) {
			res[i] = left;
			left *= a[i];//计算左边乘积
		}
		int right = 1;
		for (int i = n - 1; i >= 0; i--) {
			res[i] *= right;
			right *= a[i];//计算右边乘积
		}
		return res;
	}
};
//自己写的
class Solution {
public:
	vector<int> constructArr(vector<int>& a) {
		int len = a.size();
		vector<int> res(len);
		vector<int> left(len, 1);
		vector<int> right(len, 1);
		for (int i = 1; i < len; i++) {
			left[i] = left[i - 1] * a[i - 1];//i 左边乘积
		}
		for (int i = len - 2; i >= 0; i--) {
			right[i] = right[i + 1] * a[i + 1];//i 右边乘积
		}
		for (int i = 0; i < len; i++) {
			res[i] = left[i] * right[i];
		}
		return res;
	}
};
int main()
{
	vector<int> arr{ 1,2,3,4,5 };
	Solution().constructArr(arr);
	return 0;
}

