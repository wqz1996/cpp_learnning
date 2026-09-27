#include <vector> // vector：第 10 行首次使用
using namespace std;
//48. 旋转图像
//给定一个 n × n 的二维矩阵表示一个图像。
//将图像顺时针旋转 90 度。
//你必须在原地旋转图像，这意味着你需要直接修改输入的二维矩阵。
//请不要使用另一个矩阵来旋转图像
class Solution {
private:
	void rotateMatrix(vector<vector<int>>& matrix, int tr, int tc, int dr, int dc) {
		int times = dc - tc;//移动次数
		int tmp = 0;
		for (int i = 0; i < times; i++) {
			tmp = matrix[tr][tc + i];//将上边移动到右边，从左往右遍历因此tc+i,在上边因此是tr
			matrix[tr][tc + i] = matrix[dr - i][tc];//左边元素移动到上边，从下往上遍历因因此dr-i,在左边因此tc
			matrix[dr - i][tc] = matrix[dr][dc - i];//下边元素移动到左边，从右往左遍历因因此dc-i,在下边因此dr
			matrix[dr][dc - i] = matrix[tr + i][dc];//右边元素移动到下边，从上往下遍历因因此tr+i,在右边因此dc
			matrix[tr + i][dc] = tmp;
		}
	}
public:
	void rotate(vector<vector<int>>& matrix) {
		int tr = 0;//记录左上角
		int tc = 0;
		int dr = matrix.size() - 1;//记录右下角边界
		int dc = matrix[0].size() - 1;
		while (tr < dr) {
			rotateMatrix(matrix, tr++, tc++, dr--, dc--);//从外圈开始逐渐向内圈收缩
		}

	}
};
int main()
{

	return 0;
}

