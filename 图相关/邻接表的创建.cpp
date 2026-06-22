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
typedef char VertexType;
typedef int EdgeType;
const int MAXVEX = 10;
typedef struct EdgeNode {//定义顶点结构
	int adjvex;
	EdgeType weight;
	EdgeNode *next;
};
typedef struct VertexNode {//边表结点
	VertexType data;
	EdgeNode* firstedge;
}VertexNode,AdjList[MAXVEX];
typedef struct GraphAdjList{//图的结构
	AdjList adjList;//
	int numVertexes, numEdges;//顶点数量，边的数量
};
void CreateAlGraph(GraphAdjList* G) {
	int i, j, k;
	EdgeNode* e;
	cin >> G->numVertexes >> G->numEdges;//输入顶点数目，边的数目
	for (i = 0; i < G->numVertexes; i++) {
		cin >> G->adjList[i].data;//输入顶点信息
		G->adjList[i].firstedge = NULL;//边表指针指向NULL
	}
	for (k = 0; k < G->numEdges; k++) {
		cin >> i >> j;
		/******邻接表*********/
		e = new EdgeNode;//创建边表结点
		e->adjvex = j;//边表结点存储邻接顶点号
		e->next = G->adjList[i].firstedge;//边表结点指针指回当前节点的指针域
		G->adjList[i].firstedge = e;//当前顶点指向边表结点
		/******逆邻接表*********/
		e = new EdgeNode;//创建边表结点
		e->adjvex = i;//边表结点存储邻接顶点号
		e->next = G->adjList[j].firstedge;//边表结点指针指回当前节点的指针域
		G->adjList[j].firstedge = e;//当前顶点指向边表结点
	}

}
int main() {


	
	return 0;
}