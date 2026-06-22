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
int getcount(string str, int len1, int len2) {
	int count = 0;
	int strlen = str.size();
	for (int len = len1; len <= len2; len++) {//长度在len1到len2之间
		for (int i = 0; i < strlen && i < len; i++) {//
			count += (26 - (str[i] - 'a' + 1)) * pow(26, strlen - i - 1);
			if (len > strlen)
				count += pow(26, len - strlen);

		}
	}
	return count;
}
int main()
{
	string s1, s2;
	int len1, len2;
	while (cin >> s1 >> s2 >> len1 >> len2) {
		int s1len = s1.size();
		int s2len = s2.size();
		int count1 = getcount(s1, len1, len2);//计算大于s1且长度在len1到len2之间的字符串个数
		int count2 = getcount(s2, len1, len2);//计算大于s2且长度在len1到len2之间的字符串个数
		int res = count1 - count2 - 1;
	}

	return 0;

}


