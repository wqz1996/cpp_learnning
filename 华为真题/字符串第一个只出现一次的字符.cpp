#include <utility> // 使用处：第 12 行的 pair
#include <algorithm> // 使用处：第 27 行的 min(
#include <iostream> // 使用处：第 11 行的 cin
#include <string> // 使用处：第 9 行的 string
#include <map> // 使用处：第 12 行的 map<
using namespace std;
//输入n个整数，输出其中最小的k个。
int main() {
	string s;

	while (cin >> s) {
		map<char, pair<int,int>> m;
		for (int i = 0; i < s.size(); i++) {
			if (m.find(s[i]) == m.end()) {
				m[s[i]].first = i;
			}			
			m[s[i]].second += 1 ;		
		}
		char res;
		int minindex=s.size()-1;
		bool find = false;
		for (auto mp : m) {
			if (mp.second.second == 1) {
				find = true;
				if (mp.second.first <= minindex)
					res = mp.first;
				minindex = min(mp.second.first, minindex);				
			}		
		}
		if (find)
			cout << res << endl;
		else
			cout << -1 << endl;

	}
	
	return 0;
}
//
int main() {
	string s;

	while (cin >> s) {
		for (int i = 0; i < s.size(); i++) {
			if (s.find_first_of(s[i]) == s.find_last_of(s[i])) {
				cout << s[i] << endl;
				break;
			}
			if (i == s.size() - 1) {
				cout << -1 << endl;
				break;
			}
				
		}

	}

	return 0;
}

