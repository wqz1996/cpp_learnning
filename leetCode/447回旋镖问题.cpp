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
/************447回旋镖的数量********************/
//给定n对平面上的点坐标，回旋镖由(i,j,k)，其中i和j之间
//距离和i到k之间的距离相等
//假设n最大为500
class Solution {
private:
	int dis(int x1, int y1,int x2,int y2) {
		return ((x1-x2)* (x1 - x2) + (y1-y2)* (y1 - y2));//表示距离的平方，防止开根号导致计算不精确
	}
public:
	int numberOfBoomerangs(vector<vector<int>>& points) {
		int res = 0;
		for (int i = 0; i < points.size(); i++) {
			unordered_map<int, int> record;//记录到i的距离以及个数
			for (int j = 0; j < points.size(); j++) {
				if (i != j)
					record[dis(points[i][0], points[i][1], points[j][0], points[j][1])]++;
			}
			for (unordered_map<int, int>::iterator it = record.begin(); it != record.end(); it++) {
				if (it->second >= 2) {//值
					res += (it->second) * (it->second - 1);
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
	int tag = 9;

	return 0;
} 