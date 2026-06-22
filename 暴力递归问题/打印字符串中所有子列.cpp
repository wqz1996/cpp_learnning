#include<algorithm>//包含堆操作
#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<stack>//栈
#include<queue>//队列
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

