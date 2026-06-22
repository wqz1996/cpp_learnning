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
using namespace std;
struct Node {
	int data;
	struct Node* father;
};
/******************并查集*******************************************/
class UnionFindset {
public:
	unordered_map<Node*, Node*> fathermap;//key:child value:father
	unordered_map<Node*, int> sizemap;//key:集合 value:总节点数
	UnionFindset(list<Node*> nodes) {
		makeSet(nodes);
	}
private:
	void makeSet(list<Node*> nodes) {//保存集合信息
		for (Node* node : nodes) {
			fathermap.insert({ node, node });//将链表的每个节点对应的父节点保存
			sizemap.insert({ node,1 });//将链表中每个节点长度设为1
		}
	}
	/******************递归版本找代表节点****************************/
	Node* findhead(Node* node) {//找给定节点的代表节点
		Node* father = fathermap[node];
		if (father != node) {
			father = findhead(father);
		}
		fathermap.insert({ node,father });//将代表节点设为所有节点的父节点
		return father;
	}
	/*********************非递归版本找代表节点******************************************/
	Node* findheadUnorder(Node* node) {
		stack<Node*> s;
		Node* cur = node;
		Node* parent = fathermap[cur];
		while (cur != parent) {//向上找到代表节点
			s.push(cur);
			cur = parent;
			parent = fathermap[cur];
		}
		while (!s.empty()) {//将所有节点的父节点改为代表节点
			fathermap.insert({ s.top(),parent });
			s.pop();
		}
		return parent;
	}
	/*******************************************/
public:
	bool isSameSet(Node* a, Node* b) {
		return findhead(a) == findhead(b);
	}
	void UnionSet(Node* a, Node* b) {
		if (a == NULL || b == NULL) {
			return;
		}
		Node* ahead = findhead(a);
		Node* bhead = findhead(b);
		if (ahead != bhead) {
			int asize = sizemap[ahead];
			int bsize = sizemap[bhead];
			if (asize <= bsize) {//短的连接到长的链上
				fathermap.insert({ ahead,bhead });//将a的代表节点指向b的代表节点完成连接
				sizemap.insert({ bhead,asize + bsize });//修改b链的大小,a头节点的大小可以释放但是以后不用了
			}
			else {
				fathermap.insert({ bhead,ahead });//同上
				sizemap.insert({ ahead,asize + bsize });
			}
		}
	}

};
/********************************************************************/
/***************岛问题********************/
//矩阵中只有0，1两个值，每个位置可以和上下左右四个位置相连
//如果有一片1连在一起。则这部分叫做岛。求一个矩阵中岛的数量
//解：1）可以用深度搜索
//	  2)当矩阵特别大时，需要将矩阵划分成多块并行计算，需要用到并查集
void infect(int* m, int i, int j, int N, int M) {
	if (i < 0 || i >= N || j < 0 || j >= M || m[M * i + j] != 1) {//越界或当前不为1则返回
		return;
	}
	m[M * i + j] = 2;//将当前位置改为2
	infect(m, i + 1, j, N, M);//感染下
	infect(m, i, j + 1, N, M);//感染右
	infect(m, i - 1, j, N, M);//感染上
	infect(m, i, j - 1, N, M);//感染左
}
int countislands(int* m, int r, int c) {
	if (m == NULL)
		return 0;
	int N = r;
	int M = c;
	int res = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (m[c * i + j] == 1) {//当前为1则岛数加一，并将包括该位置所有连成一片的1全部改为2
				res++;
				infect(m, i, j, N, M);
			}
		}
	}
	return res;
}
//用并查集求解，将岛划分，并行完成，收集各任务的结果，设计边界合并方法（并查集）
//记录感染中心，将同一个感染中心感染的元素放在一个集合中，合并时将边界上的两个集合进行合并，
//合并以后两个集合为一个集合，再次判断时可以避免重复。
int main()
{

	int m[][7] = { {1,1,1,1,0,0,0}, {1,0,0,0,1,1,0},{1,1,0,0,0,0,1} };//岛问题验证，答案：3
	cout << countislands((int*)m, 3, 7) << endl;
	return 0;

}

