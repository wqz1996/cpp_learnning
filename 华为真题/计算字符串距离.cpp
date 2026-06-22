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
#define N 100
using namespace std;
//lev[i][j]用来表示字符串a的[1...i]和字符串b[1...j]的levenshtein距离；
//插入和删除操作互为逆过程：a删除指定字符变b等同于b插入指定字符变a；
//如果a[i] == b[j]，则说明a[i]和b[j]分别加入a，b之后不会影响levenshtein距离，lev[i][j] = lev[i - 1][j - 1] + 0;
//如果a[i] != b[j]，则需要考虑3种情况的可能：
//a中插入字符，即lev[i][j] = lev[i - 1][j] + 1;
//b中插入字符，即lev[i][j] = lev[i][j - 1] + 1;
//a[i]替换成b[j]，lev[i][j] = lev[i - 1][j - 1] + 1;
//取这4种情况的最小值。
int main() {
	string s1, s2;
	while (cin >> s1 >> s2) {
		int len1 = s1.size();
		int len2 = s2.size();
		vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));
		dp[0][0] = 0;
		for (int i = 1; i <= len1; i++)
			dp[i][0] = i;
		for (int i = 1; i <= len2; i++)
			dp[0][i] = i;
		for (int i = 1; i <= len1; i++) {
			for (int j = 1; j <= len2; j++) {
				int cost = 0;
				if (s1[i - 1] != s2[j - 1])
					cost = 1;
				dp[i][j] = min(dp[i - 1][j] + 1, min(dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost));

			}
		}
		cout << dp[len1][len2] << endl;
	}
	return 0;
}
