#include <iostream> // 使用处：第 16 行的 cout
using namespace std;
#define length 4
/****************给定数组，任意求和，能否得到指定sum***********************************/
bool isSum(int arr[], int i, int sum,int aim)
{
	if (i== length-1)//
		return sum == aim;
	return isSum(arr, i + 1, sum,aim)||isSum(arr, i + 1, sum + arr[i], aim);//当前位置与之后任选的几个数数求和，只要有aim出现返回
}
/*------------------------------------------------------------------------------------------*/
int main()
{
	int arr[length] = { 3,2,7,13 };
	int desire_sum = 5;
	cout << isSum(arr, 0, 0, desire_sum) << endl;

	return 0;	
}

