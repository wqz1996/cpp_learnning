#include <algorithm> // 使用处：第 67 行的 min_element(
#include <iostream> // 使用处：第 57 行的 cin
#include <vector> // 使用处：第 8 行的 vector
using namespace std;
//并查集
class Union {
public:
	vector<int> parent;
	void creatUnion(int n) {//初始化n个并查集
		parent = vector<int>(n);
		for (int i = 0; i < n; i++) {
			parent[i] = i;//当前元素的值为当前元素的索引
		}
	}
	int Findroot(int i) {
		int root = i;
		while (root != parent[root])//找到老大
			root = parent[root];
		while (i != parent[i]) {//压缩路径，将所有直接指向真正老大
			int temp = parent[i];
			parent[i] = root;
			i = temp;
		}
		return root;

	}
	bool isSameset(int p, int q) {//判断p，q是否为同一个集合
		return Findroot(p) == Findroot(q);
	}
	void UnionXY(int p, int q) {
		int qroot = Findroot(q);
		int proot = Findroot(p);
		if (proot < qroot)//p老大小则p是q的老大
			parent[qroot] = proot;
		else
			parent[proot] = qroot;
	}
};

//美团小区订单合并问题
//输入n为小区个数，m为小区之间的关系
//x,y为x和y是同一个小区
//优先输出订单编号较小的最小的小区的集合
//例：
//输入:
//5 5
//1 3
//2 4
//3 3
//4 4
//5 4
//输出：
//13245
int main()
{
	int n, m;
	while (cin >> n >> m) {
		Union Uset;
		Uset.creatUnion(n);//初始化集合
		int x, y;
		for (int i = 0; i < m; i++) {
			cin >> x >> y;
			Uset.UnionXY(x-1, y-1);//进行集合合并
		}
		int count = 0;
		while (count < n) {
			int minval = *min_element(Uset.parent.begin(), Uset.parent.end());//找到当前最小的小区
			for (int i = 0; i < Uset.parent.size(); i++) {//从小到大输出订单编号
				if (Uset.parent[i] == minval) {
					count++;
					cout << i + 1 ;
					Uset.parent[i] = n + 1;
				}
			}
		}
		cout << endl;
	}
	 

	
	return 0;
}


