#include <vector> // 使用处：第 5 行的 vector
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