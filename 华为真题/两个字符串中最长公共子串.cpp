#include <iostream>
#include <string>
using namespace std;
int main() {
	string s1,s2;
	while (cin >> s1>>s2) {
		if (s1.size() > s2.size())//从短的字符串中遍历，因此需要将s1赋值为较短的字符串
			swap(s1, s2);
		int len1 = s1.size();
		int len2 = s2.size();
		int maxlen = 0;
		string res;
		for (int i = 0; i < len1; i++) {
			for (int j = i + 1; j < len1; j++) {
				string temp = s1.substr(i, j-i+1);//s1中取字符串
				int len = temp.size();
				if (s2.find(temp) != string::npos) {
					if (len > maxlen) {//保存长度大的子串，长度相等则保留之前的res
						res = temp;
						maxlen = len;
					}					
				}
			}
		}
		cout << res << endl;
	}
	return 0;
}