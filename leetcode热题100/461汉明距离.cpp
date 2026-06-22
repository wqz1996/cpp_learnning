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
/**********************461汉明距离*************************/
//两个整数之间的汉明距离指的是这两个数字对应二进制位不同的位置的数目
//给出两个整数 x 和 y，计算它们之间的汉明距离。
//注：0 ≤ x, y < 2^31.
class Solution {
public:
	int hammingDistance(int x, int y) {
		int yihuo;
		int sum = 0;
		yihuo = x ^ y;//异或记录对应位不一样的
		while (yihuo!=0) {
			if (yihuo & 1)//判断最后一位是否是1
				sum++;
			yihuo=yihuo >> 1;//记录结果右移一位
		}
		return sum;
		
	}
};
int main()
{
	cout << Solution().hammingDistance(1, 4);
	return 0;
}

