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
#include<assert.h>
#include<set>
#include<map>
using namespace std;
class Solution {
private:
	void rotateEdge(vector<vector<int>>& m, int tr, int tc, int dr, int dc) {
		int times = dc - tc;
		int tmp = 0;
		for (int i = 0; i != times; i++) {
			tmp = m[tr][tc + i];
			m[tr][tc + i] = m[tr + i][dc];
			m[tr + i][dc] = m[dr][dc - i];
			m[dr][dc - i] = m[dr - i][tc];
			m[dr - i][tc] = tmp;
		}
	}
public:
	vector<vector<int>> RotaeMatrix(vector<vector<int>>& matrix) {
		int tr = 0;
		int tc = 0;
		int dr = matrix.size() - 1;
		int dc = matrix[0].size() - 1;
		while (tr < dr) {
			rotateEdge(matrix, tr++, tc++, dr--, dc--);
		}
		return matrix;
	}
};
int main() {
	vector<vector<int>> arr = { {0,1,2},{3,4,5},{6,7,8} };
	vector<vector<int>> res=Solution().RotaeMatrix(arr);

	
	return 0;
}