#include <cstring> // 使用处：第 13 行的 strlen(
#include <algorithm> // 使用处：第 7 行的 swap(
#include <iostream> // 使用处：第 14 行的 cout
#include <string> // 使用处：第 25 行的 string
using namespace std;
/********打印字符串全排列***有问题待解决****/
void swap(char s[], int i, int j){
	char temp = s[i];
	s[i] = s[j];
	s[j] = temp;
}
void printAllpermutation(char s[], int i) {
	if (i == strlen(s)-1) {
		cout << s << endl;
	}
	for (int j = i ; j < strlen(s); j++)
	{
		swap(s, i, j);
		printAllpermutation(s, i + 1);
		
	}
}
int main()
{
	string str = "abc";
	char s[10];
	strcpy(s, str.c_str());//string 转为字符数组
	printAllpermutation(s, 0);



	return 0;
}

