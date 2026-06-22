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
#include<stdio.h>
#include<malloc.h>
#include<stdio.h>
#include<string.h>
using namespace std; 
//图的邻接矩阵表示
struct MGraph {
	vector<int> vexs;
	vector<vector<int>> arc;
	int numvex;
	int numedge;
};
void CreatMGraph(MGraph& G) {//无向图
	int from, to , w;//起始顶点、结束顶点、权值
	cin >> G.numvex >> G.numedge;//输入顶点数量、边的数量
	G.vexs = vector<int>(G.numvex);
	G.arc = vector<vector<int>>(G.numvex, vector<int>(G.numvex, INT_MAX));//没连接关系值为INT_MAX
	for (int i = 0; i < G.numvex; i++)
		cin >> G.vexs[i];//输入顶点值
	for (int i = 0; i < G.numedge; i++) {
		cin >> from >> to >> w;
		G.arc[from][to] = w;//对应位置赋予权值
		G.arc[to][from] = G.arc[from][to];//无向图，矩阵对称，若是有向图则去掉该行
	}		
}
//图的邻接表表示
struct EdgeNode {//边表结点
	int data;
	int weight;
	EdgeNode* next;
};
struct VertexNode {//顶点表结点
	int data;//顶点值
	EdgeNode* firstedge;//边表头指针
};
struct GraphAdjList {
	vector<VertexNode> adjList;//顶点表
	int numVex;//图中顶点数量
	int numEdge;//边的数量
};
void CreatALGraph(GraphAdjList& G) {//头插法建立邻接表
	int from, to, w;//输入起始顶点序号、结束顶点序号、权值	
	EdgeNode* e;
	cin >> G.numVex >> G.numEdge;
	G.adjList = vector<VertexNode>(G.numVex);
	for (int i = 0; i < G.numVex; i++) {
		cin >> G.adjList[i].data;//输入顶点值
		G.adjList[i].firstedge = NULL;//边表置空
	}
	for (int i = 0; i < G.numEdge; i++) {
		cin >> from >> to >> w;
		e = new EdgeNode;//创建邻接点
		e->weight = w;//赋予权值
		e->data = to;//邻接点赋值
		e->next = G.adjList[from].firstedge;//头插
		G.adjList[from].firstedge = e;

		/**********无向图from->to和to->from同时插入即可**********/
		e = new EdgeNode;//创建邻接点
		e->weight = w;//赋予权值
		e->data = from;//邻接点赋值
		e->next = G.adjList[to].firstedge;//头插
		G.adjList[to].firstedge = e;
	}
}
//图的DFS
/*************邻接矩阵的DFS********************/
vector<bool> visit;
vector<int> res;
vector<int> DFS(MGraph G, int i) {
	int j;
	visit[i] = true;
	res.push_back(G.vexs[i]);
	for(j=0;j<G.numvex;j++)
}

int main()
{
	GraphAdjList  G;
	CreatALGraph(G);
	return 0;
}