#include <functional> // 使用处：第 15 行的 greater<
#include <algorithm> // 使用处：第 33 行的 sort(
#include <iostream> // 使用处：第 56 行的 cout
#include <queue> // 使用处：第 15 行的 priority_queue
#include <vector> // 使用处：第 13 行的 vector
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

