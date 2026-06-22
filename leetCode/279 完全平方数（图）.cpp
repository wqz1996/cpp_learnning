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
/************279完全平方数*******************/
//给定正整数n，找到若干个完全平方数（1，4，9，16。。。）
//使得它们的和等于n，使得完全平方数个数最少
//提示：无权图
class Solution {
public:
	int numSquares(int n) {
		assert(n > 0);
		queue<pair<int, int>> q;//第一个int表示第几个数字，第二个int表示图中经历了多少路径
		q.push(make_pair(n, 0));
		vector < bool > visited(n + 1, false);
		visited[n] = true;//判断该数字是否访问过
		while (!q.empty()) {//广度优先遍历
			int num = q.front().first;//数字
			int step = q.front().second;//走的步数
			q.pop();
			
			for (int i = 1;; i++) {//
				int a = num - i * i;
				if (a < 0)
					break;
				if (a == 0)
					return step + 1;
					if (!visited[a]) {
						q.push(make_pair(a, step + 1));
						visited[a] = true;
					}
							
			}


		}
		throw invalid_argument("No Solution");


	}
};
int main() {
	cout<<Solution().numSquares(6)<<endl;

	return 0;
} 