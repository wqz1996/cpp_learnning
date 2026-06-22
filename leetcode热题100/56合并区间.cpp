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
//56. 合并区间
//给出一个区间的集合，请合并所有重叠的区间。
bool compare(const vector<int>& A, const  vector<int>& B) {//按照第一个元素升序排序
	return A[0] < B[0];
}
class Solution {
public:
	vector<vector<int>> merge(vector<vector<int>>& intervals) {
		vector<vector<int>> res;
		sort(intervals.begin(), intervals.end(), compare);
		for (int i = 0; i < intervals.size(); i++) {
			int L = intervals[i][0];//区间左边界
			int R = intervals[i][1];//区间右边界
			if (res.empty() || res.back()[1] < L) {//res为空或者res最后一组空间的右边界小于当前遍历区间的左边界
				res.push_back({ L,R });
			}
			else {
				res.back()[1] = max(res.back()[1], R);//修改res最后一组空间的右边界
			}
		}
		return res;
	}
};
int main()
{
	vector<vector<int>> intervals = { {2, 6}, {1,3 },{8, 10},{15, 18} };
	Solution().merge(intervals);
	return 0;
}

