#include <iostream> // 使用处：第 11 行的 cin
#include <string> // 使用处：第 10 行的 string
#include <vector> // 使用处：第 20 行的 vector
#include <assert.h> // 使用处：第 34 行的 assert(
using namespace std;
//MP3 Player因为屏幕较小，显示歌曲列表的时候每屏只能显示几首歌曲，用户要通过上下键才能浏览所有的歌曲。
//为了简化处理，假设每屏只能显示4首歌曲，光标初始的位置为第1首歌。
int main() {
	int n;
	string s;
	while (cin >> n >> s) {
		int len = s.size();
		int p = 0;
		int up = 0;
		int down = 0;
		if (n <= 4)
			down = n - 1;
		else
			down = 3;
		vector<int> board(n);
		for (int i = 1; i <= n; i++)
			board[i - 1] = i;
		if (n <= 4) {//歌曲数目小于等于4
			for (int i = 0; i < len; i++) {
				if (s[i] == 'U') {
					if (p == 0) {//指向第一个时
						p = board.size() - 1;//直接跳到最后一个
					}
					else {//普通情况正常移动
						p--;
					}
				}
				else {
					assert(s[i] == 'D');
					if (p == board.size() - 1) {
						p = 0;
					}
					else {
						p++;
					}
				}
			}
			for (int i = up; i <= down; i++)
				cout << board[i] << ' ';
			cout << endl;
			cout << board[p] << endl;
		}
		else {
			for (int i = 0; i < len; i++) {
				if (s[i] == 'U') {
					if (p == 0) {//调整窗口位置，并移动光标到最后
						up = board.size() - 4;
						down = board.size() - 1;
						p = board.size() - 1;
					}
					else if (p <= down && p > up) {//p在(up,down]区间内向上运动即可
						p--;
					}
					else if (p == up) {//p碰到上界则移动窗口同时移动光标
						p--;
						down--;
						up--;
					}
				}
				else {
					assert(s[i] == 'D');
					if (p == board.size() - 1) {
						up = 0;
						down = 3;
						p = 0;
					}
					else if (p < down && p >= up)
						p++;
					else if (p == down) {
						p++;
						down++;
						up++;
					}

				}


			}
			for (int i = up; i <= down; i++)
				cout << board[i] << ' ';
			cout << endl;
			cout << board[p] << endl;
		}



	}
	return 0;
}
