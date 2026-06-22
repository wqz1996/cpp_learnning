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
//密码要求:
//1.长度超过8位
//2.包括大小写字母.数字.其它符号, 以上四种至少三种
//3.不能有相同长度大于2的子串重复
int main() {
	string s;
	vector<string> res;
	while (cin>>s) {
		bool isright = true;
		if (s.size() <= 8) {//长度判断
			isright = false;
		}
		int kind = 0;
		vector<int> board(4);
		for (int i = 0; i < s.size(); i++) {//种类判断
			if (s[i] >= '0' && s[i] <= '9')
				board[0] = 1;
			else if (s[i] >= 'A' && s[i] <= 'Z')
				board[1] = 1;
			else if (s[i] >= 'a' && s[i] <= 'z')
				board[2] = 1;
			else
				board[3] = 1;	
			
		}
		for (int i = 0; i < 4; i++)
			kind += board[i];
		if (kind < 3)
			isright = false;
		for (int i = 0; i < s.size(); i++) {//重复字符串判断
			string sub=s.substr(i,3);
			if (s.find(sub, i + 3) != string::npos) {
				isright = false;
				break;
			}				
		}
		if (isright)
			cout << "OK" << endl;
		else
			cout << "NG" << endl;
	
	}
	return 0;
}

