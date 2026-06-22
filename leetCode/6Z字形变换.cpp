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
/*************Z字型变换*****************************/
class Solution {
public:
	string convert(string s, int numRows) {
		string ans;
		if (s.empty())//字符为空则返回空
			return ans;
		if (s.size() <= numRows)//行数大于s长度，返回原字符
			return ans + s;
		if (s.size() == 2)//s为2时，返回原字符
			return ans + s;
		if (numRows == 1)//行数为1时，返回原字符
			return ans + s;

		int len = s.size();//字符长度
		int integ = len / (2 * numRows - 2);//一个单元的字符个数
		int res = len % (2 * numRows - 2);//除去完整单元的余下字符个数
		int rescol;
		if (res == 0) {//余数为0则除去完整单元的列出以外剩下列数为0
			rescol = 0;
		}
		else {//余数不为0则除去完整单元的列以外剩下的列数
			rescol = res > numRows ? 1 + res - numRows : 1;
		}
		int wholeCol = (numRows - 1) * integ + rescol;
		vector<vector<char>> board(numRows, vector<char>(wholeCol, '#'));//创建二维字符数组
		//col=(row-1)*(len/(2*row-2))+rescol
		int m=0, n=0;//board起始点
		bool flag = true;
		board[m][n] = s[0];
		for (int i = 1; i < len; i++) {
			if (flag) {
				board[++m][n] = s[i];//安排从上到下元素
				if (m == numRows-1) {
					flag = false;//到达最后一行后切换安排模式
				}
					
			}
			else {
				board[--m][++n] = s[i];//安排对角元素
				if (m == 0) {//回到第一行后切换安排模式
					flag = true;
				}
			}
		}
		for (int i = 0; i < numRows; i++) {//按顺序输出字符
			for (int j = 0; j < wholeCol; j++) {
				if (board[i][j] != '#') {
					ans += board[i][j];
				}
			}
		}
		return ans;
	}
};
/*******************简便方法********************/
class Solution {
public:
	string convert(string s, int numRows) {
		if (numRows == 1)
			return s;//numRows为1时，返回原字符数组即可
		vector<string> board(min(numRows, (int)s.size()));
		string ans;
		int rol = 0;//将s[i]安排在第rol行
		bool flag = false;//切换安排模式
		for (int i = 0; i < s.size(); i++) {//遍历s字符串
			board[rol] += s[i];//将s[i]加在board的第rol行的末尾
			if (rol == 0 || rol == board.size() - 1)//边界判断
				flag = !flag;//切换安排模式
			rol += flag ? 1 : -1;//行数根据安排模式进行+1或-1

		}
		for (int i = 0; i < board.size(); i++)//将board中每行的字符串连在一起即为答案
			ans += board[i];
		return ans;
	}
};
int main()
{
	string s{ "LEETCODEISHIRING" };
	string s1{ "A" };
	cout<<Solution().convert(s1,1)<<endl;
	return 0;
}

