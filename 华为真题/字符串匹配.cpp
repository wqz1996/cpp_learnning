#include <iostream> // 使用处：第 7 行的 cin
#include <string> // 使用处：第 6 行的 string
using namespace std;
//判断短字符串中的所有字符是否在长字符串中全部出现
int main() {
	string s1,s2;
	while (cin >> s1 >> s2) {
		bool res = true;
		for (int i = 0; i < s1.size(); i++) {
			if (s2.find(s1[i])!=string::npos)
				continue;
			else {
				res = false;
				break;
			}

		}
		if(res)
			cout<<"true"<<endl;
		else
			cout << "false" << endl;

	}
	return 0;
}
