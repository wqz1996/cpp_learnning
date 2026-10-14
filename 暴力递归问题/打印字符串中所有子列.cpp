#include <cstring> // 使用处：第 6 行的 strlen(
#include <iostream> // 使用处：第 8 行的 cout
#include <string> // 使用处：第 5 行的 string
using namespace std;
void printAllsub(char str[], int i, string res) {
	if (i == strlen(str))
	{
		cout << res;
		return;
	}
	printAllsub(str, i + 1, res);
	printAllsub(str, i + 1, res + str[i]);

}
/******************************************************/
/*
char ch[]="ABCDEFG";
string str(ch);//将char字符数组转换为string类型
string str=ch;//将char字符数组转换为string类型
*/


int main()
{
	string test = "abc";
	char s[10];
	strcpy(s, test.c_str());//将string字符串转换为字符串数组 例"abc"->['a','b','c']
	printAllsub(s,0," ");
	return 0;
}

