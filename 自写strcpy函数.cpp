#include<algorithm>//包含堆操作
#include<iostream>
using namespace std;
char* my_strcpy(char* dst, const char* src, int cnt)
{
	if (dst == NULL || src == NULL)
		return NULL;

	char* ret = dst;

	if (dst >= src && dst <= src + cnt - 1) //内存重叠，从高地址开始复制
	{
		dst = dst + cnt - 1;
		src = src + cnt - 1;
		while (cnt--)
			*dst-- = *src--;
	}
	else    //正常情况，从低地址开始复制
	{
		while (cnt--)
			*dst++ = *src++;
	}
	*dst = '\0';
	return ret;
}
int main() {
	string a, b;
	cin >> a >> b;
	char* strA=(char *)a.c_str();
	char* strB = (char*)b.c_str();
	int len = sizeof(strB) / sizeof(char);
	char* res = my_strcpy(strA, strB, len + 1);
	cout << res << endl;

	return 0;
}