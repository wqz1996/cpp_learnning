#include <iostream> // 使用处：第 11 行的 cout
#include <vector> // 使用处：第 33 行的 vector
using namespace std;
// 面试题4：二维数组中的查找
// 题目：在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按
// 照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个
// 整数，判断数组中是否含有该整数。
bool findnum(int* matrix, int c, int r, int num) {
	
	if (matrix == nullptr) {
		cout << "ERROR" << endl;
		return false;
	}
	int index_r = 0;
	int index_c = c - 1;
	while (index_r <= r - 1 && index_c >= 0) {
		if (matrix[index_r * c + index_c] == num) {//matrix[index_r * c + index_c]->matrix[index_r][index_c]
			return true;
		}
		if (matrix[index_r * c + index_c] > num) {
			index_c--;
		}
		else {
			index_r++;
		}
	}
	return false;
	
}
/************在线IDE*****************/
class Solution {
public:
	bool Find(int target, vector<vector<int> > array) {
		if (array.empty()) {
			return false;
		}
		int r = array.size();
		int c = array[0].size();
		int index_r = 0;
		int index_c = c - 1;
		while (index_r <= r-1 && index_c >= 0) {
			if (array[index_r][index_c] == target)
				return true;
			if (array[index_r][index_c] > target)
				index_c--;
			else
				index_r++;
		}
		return false;
	}
};
int main()
{
	vector<vector<int>> m{ {1,2,8,9},{4,7,10,13} };
	int matrix[][4] = { {1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15} };
	int m2[][4] = { {1,2,8,9},{4,7,10,13} };
	Solution s;
	//cout<<s.Find(7, m)<<endl;
	cout << findnum((int*)m2, 4, 2,7) << endl;
	return 0;

}



