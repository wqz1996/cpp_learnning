#include <cstdlib> // 使用处：第 26 行的 system
#include <algorithm> // 使用处：第 23 行的 sort(
#include <iostream> // 使用处：第 25 行的 cout
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

