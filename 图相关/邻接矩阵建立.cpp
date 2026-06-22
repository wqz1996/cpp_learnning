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
const int MAXVEX = 100;
const int INF = 65535;
typedef struct MyGraph {
	VertexType vexs[MAXVEX];
	EdgeType arc[MAXVEX][MAXVEX];
	int numVertexes,numEdges;
};
void CreateMyGraph(MyGraph* G) {
	int i, j, k, w;
	cin >> G->numVertexes >> G->numEdges;//输入顶点数和边数
	for (i = 0; i < G->numVertexes; i++) {
		cin >> G->vexs[i];//输入顶点信息
	}
	for (i = 0; i < G->numVertexes; i++) {//初始化邻接矩阵
		for (j = 0; j < G->numVertexes; j++) {
			G->arc[i][j] = INF;
		}
	}
	for (k = 0; k < G->numEdges; k++) {
		cin >> i >> j >> w;//输入顶点、邻接顶点、权值
		G->arc[i][j] = w;//vi,vj对应的权值
		G->arc[j][i] = G->arc[i][j];//无向图矩阵对称
	}

}
int main() {


	
	return 0;
}