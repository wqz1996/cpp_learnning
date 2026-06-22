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
	string plusone(string s, int j) {//向上旋转
		if (s[j] == '9')
			s[j] = '0';
		else
			s[j] += 1;
		return s;
	}
	string minone(string s, int j) {//向下旋转
		if (s[j] == '0')
			s[j] = '9';
		else
			s[j] -= 1;
		return s;
	}
public:
	int openLock(vector<string>& deadends, string target) {
		set<string> visit;//记录是否访问过该节点
		set<string> dead(deadends.begin(), deadends.end());//记录死亡数字（不可达到的数字）
		//也可以将dead的值直接放到visit中记录为已经遍历过的值
		queue<string> q;
		int step = 0;
		q.push("0000");
		visit.insert("0000");
		while (!q.empty()) {//广度优先遍历，BFS
			int sz = q.size();
			for (int i = 0; i < sz; i++) {
				string cur = q.front();//当前节点
				q.pop();
				if (dead.find(cur) != dead.end())//如果是死亡数字则跳过
					continue;
				if (cur == target)//找到目标，返回step
					return step;
				for (int j = 0; j < 4; j++) {//分别转动4个密码锁
					string up = plusone(cur, j);//向上转动
					if (visit.find(up) == visit.end()) {//未遍历过则加入遍历队列中
						q.push(up);
						visit.insert(up);//记录为已经遍历
					}
					string down = minone(cur, j);//向下转动
					if (visit.find(down) == visit.end()) {
						q.push(down);
						visit.insert(down);
					}
				}
			}
			step++;
		}
		return -1;
	}
};
//双向BFS
class Solution {
private:
	string plusone(string s, int j) {//向上旋转
		if (s[j] == '9')
			s[j] = '0';
		else
			s[j] += 1;
		return s;
	}
	string minone(string s, int j) {//向下旋转
		if (s[j] == '0')
			s[j] = '9';
		else
			s[j] -= 1;
		return s;
	}
public:
	int openLock(vector<string>& deadends, string target) {
		set<string> visit;//记录是否访问过该节点
		set<string> dead(deadends.begin(), deadends.end());//记录死亡数字（不可达到的数字）
		//也可以将dead的值直接放到visit中记录为已经遍历过的值
		set<string> q1, q2;
		int step = 0;
		q1.insert("0000");
		q2.insert(target);
		while (!q1.empty() && !q2.empty()) {//广度优先遍历，BFS
			set<string> temp;
			if (q1.size() > q2.size()) {//每次扩散更小的集合，进一步减小空间增长速度
				swap(q1, q2);
			}
			for (string cur : q1) {//遍历q1节点
				if (dead.find(cur) != dead.end())
					continue;
				if (q2.find(cur) != q2.end())//判断cur是否在q2中出现，如果出现说明双向遍历相遇了
					return step;
				visit.insert(cur);//记录当前节点为已遍历

				for (int j = 0; j < 4; j++) {//分别转动4个密码锁
					string up = plusone(cur, j);//向上转动
					if (visit.find(up) == visit.end()) {//未遍历过则加入遍历队列中
						temp.insert(up);//temp用于双向遍历时交换set
					}
					string down = minone(cur, j);//向下转动
					if (visit.find(down) == visit.end()) {
						temp.insert(down);
					}
				}

			}
			step++;
			q1 = q2;
			q2 = temp;

		}
		return -1;
	}
};
int main() {

	int m, n;
	while (cin >> m >> n) {



	}

	return 0;
}