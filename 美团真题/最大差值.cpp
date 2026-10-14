#include <algorithm> // 使用处：第 13 行的 min(
using namespace std;
//有一个长为n的数组A，求满足0≤a≤bn的A[b]-A[a]的最大值。
//给定数组A及它的大小n，请返回最大差值。
class LongestDistance {
public
	int getDis(vectorint A, int n) {
		if (n = 1)
			return 0;
		int maxerr = 0;
		int minval = A[0];
		for (int i = 0; i  n; i++) {
			minval = min(minval, A[i]);
			maxerr = max(maxerr, A[i] - minval);
		}
		return maxerr;

	}
};
int main() {

	return 0;
}

