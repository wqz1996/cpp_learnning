#include<algorithm>//包含堆操作
#include<iostream>
#include<sstream>//istringstream 可以将string以空格为分隔符分割
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
//有一个直方图，用一个整数数组表示，其中每列的宽度为1，求所给直方图包含的最大矩形面积。比如，对于直
//方图[2,7,9,4],它所包含的最大矩形的面积为14(即[7,9]包涵的7x2的矩形)。
//给定一个直方图A及它的总宽度n，请返回最大矩形面积。保证直方图宽度小于等于500。保证结果在int范围内。
class MaxInnerRec {
private:
	int centerexpend(vector<int> A, int index) {//向两侧扩散
		int len = 0;
		int value = 0;
		for (int i = index + 1; i < A.size(); i++) {
			if (A[i] > A[index])
				len++;
			else
				break;
		}
		for (int i = index - 1; i >= 0; i--) {
			if (A[i] > A[index])
				len++;
			else
				break;
		}
		value = A[index] * (len + 1);
		return value;
		
	}
public:
	int countArea(vector<int> A, int n) {
		int maxvalue = 0;
		if (n == 1)
			return A[0];
		if (n == 0)
			return 0;
		for (int i = 0; i < n; i++) {
			maxvalue = max(maxvalue, centerexpend(A, i));
		}
		return maxvalue;
		
	}
};
int main() {
	vector<int> A = {3,5 };
	MaxInnerRec().countArea(A, 2);
	return 0;
}

