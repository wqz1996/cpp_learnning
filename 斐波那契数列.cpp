#include<algorithm>//包含堆操作
#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<stack>//栈
#include<queue>//队列
using namespace std;
/********斐波那契数列*******/
int Fbi(int i)//(递归方法生成)返回第i个数的数值
{
	if (i < 2)
		return i == 0 ? 0 : 1;
	return  Fbi(i - 1) + Fbi(i - 2);


}
/**********非递归**********************/
int fib0(int n)//从0开始
{
	int begin[2] = { 0,1 };
	if (n < 2)
		return begin[n];
	int first = 0;
	int second = 1;
	int cur = 0;

	for (int i = 2; i <= n; i++)
	{
		cur = first + second;
		first = second;
		second = cur;
		
	}
	return cur;
}
/**********非递归**********************/
int fib1(int n)//从1开始
{
	int begin[2] = { 1,1 };
	if (n <= 2)
		return begin[n-1];
	int first = 1;
	int second = 1;
	int cur = 0;

	for (int i = 3; i <= n; i++)
	{
		cur = first + second;
		first = second;
		second = cur;

	}
	return cur;
}
/*------------------------------------------------------------------------------------------*/
int ribitsum(int n)//兔子生子问题：有一只兔子，从出生后第3个月起每个月都生一只兔子，
                   //小兔子长到第三个月后每个月又生一只兔子，假如兔子都不死，问每个月的兔子总数为多少？
{
	int F[1000];
	F[0] = 1;
	F[1] = 1;
	F[2] = 2;
	for (int i = 3; i < n; i++)
	{
		F[i] = F[i - 1] + F[i - 2];
	}
	return F[n - 1];
}
/*------------------------------------------------------------------------------------------*/
int main()
{
	int n = 5;

	//cout << Fbi(5) << endl;
	//cout << sum_fbi(5) << endl;
	for(int i=0;i<=6;i++)
	cout << fib0(i) << endl;
	return 0;
}

