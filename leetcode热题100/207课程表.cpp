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
/*************207课程表*****************************/
// 你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。
// 在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，
// 其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。
// 例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
// 请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。
class Solution {
public:
    vector<bool> visited;      //用于记录已经访问过的节点
    vector<bool> onpath;       // 用于记录当前正在访问的路径
    vector<vector<int>> graph; // 图的邻接表
    bool hasCycle = false;     // 用于标记当前的图是否有环
    // 用邻接表建立图
    void buildGraph(vector<vector<int>>& prerequisites) {
        for (vector<int>& edge : prerequisites) {
            int from = edge[1], to = edge[0];
            // 添加一个从from 到 to的有向边 修完from才能修to
            graph[from].push_back(to);
        }
    }
    // DFS遍历
    void traverse(int s) {
        //当前节点已经在onpath里面了，则有环
        if (onpath[s])
            hasCycle = true;
        //已经遍历过的节点或者已经判断有环了则不需要在继续遍历
        if (visited[s] || hasCycle)
            return;

        visited[s] = true; // 将节点s标记为已遍历
        onpath[s] = true;  // 开始遍历s节点
        // 由于不是所有节点均互相连接,因此需要将所有节点作为起点DFS一遍
        for (int t : graph[s]) {
            traverse(t);
        }
        onpath[s] = false; // 节点s遍历完成
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        graph = vector<vector<int>>(numCourses, vector<int>());
        visited = vector<bool>(numCourses, false);
        onpath = vector<bool>(numCourses, false);
        buildGraph(prerequisites);
        //遍历图中所有节点 [0, ... numCourses-1] 共有numCourses个
        for (int i = 0; i < numCourses; i++) {
            traverse(i);
        }
        return !hasCycle;
    }
};
int main()
{

	return 0;
}

