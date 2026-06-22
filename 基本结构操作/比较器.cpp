#include<algorithm>//包含堆操作
#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<stack>//栈
#include<queue>//队列
using namespace std;

struct student {
	int ID;
	int Age;
	int Score;
};
student stu[3] = {
	{1, 18, 88},
	{2, 19, 90},
	{3, 20, 70}
};
bool comparator(const student& a, const student& b)//按照成绩升序排列 70 88 90
{
	return (a.Score < b.Score);
}

int main()
{
	sort(stu, stu + 3, comparator);
	for (int i = 0; i < 3; i++)
		cout << stu[i].ID << ' ' << stu[i].Age << ' ' << stu[i].Score << endl;
	system("pause");
	return 0;
}

