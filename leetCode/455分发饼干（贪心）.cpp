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
/*************455分发饼干*****************************/
//i个孩子，每个孩子胃口为gi
//j个饼干，尺寸为sj
//分配饼干满足尽可能多的孩子，输出最大数量
class Solution {
public:
	int findContentChildren(vector<int>& g, vector<int>& s) {
		int nums = 0;
		priority_queue<int,vector<int>,greater<int>> q1(g.begin(),g.end());
		priority_queue<int, vector<int>, greater<int>> q2(s.begin(), s.end());
		while (!q1.empty() && !q2.empty()) {
			if (q2.top() >= q1.top()) {
				nums++;
				q1.pop();
				q2.pop();
			}
			else {
				q2.pop();
			}				

		}
		return nums;
	}

	int findContentChildren(vector<int>& g, vector<int>& s) {
		int nums = 0;
		sort(g.begin(), g.end(),greater<int>());
		sort(s.begin(), s.end(),greater<int>());
		int si = 0, gi = 0;
		while (si < s.size() && gi < g.size()) {
			if (s[si] >= g[gi]) {
				nums++;
				si++;
				gi++;
			}
			else {
				gi++;
			}

		}

		return nums;
	}
};

int main()
{
	vector<int> g{ 1,2 };
	vector<int> s{ 1,2,3 };
	cout<<Solution().findContentChildren(g, s)<<endl;
	return 0;
}

