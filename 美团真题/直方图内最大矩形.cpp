#include <algorithm> // 使用处：第 36 行的 max(
#include <vector> // 使用处：第 9 行的 vector
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

