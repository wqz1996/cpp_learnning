#include <iostream> // 使用处：第 22 行的 cin
#include <string> // 使用处：第 5 行的 string
#include <cmath> // 使用处：第 10 行的 pow
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


