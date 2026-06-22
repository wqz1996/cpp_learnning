#include<algorithm>//包含堆操作
#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<stack>//栈
#include<queue>//队列
using namespace std;
/********汉诺塔问题*******/
/*void func(int rest, int down, string from, string help, string to) {
	if (rest == 1)
	{
		cout << " Move " << down << " from " << from << " to " << to << endl;
	}
	else {
		func(rest - 1, down - 1, from, to, help);
		func(1, down, from, help, to);
		func(rest - 1, down - 1, help, from, to);
	}
}
void hanoi(int n) {
	if (n > 0) {
		func(n, n, "left", "mid", "right");
	}
}*/

void process(int N, string from, string to, string help) {
	if (N == 1){
		cout << "Move 1 from " << from << " to " << to<<endl;
		return;
	}
	else {
		process(N - 1, from, help, to);
		cout << "Move " << N << " from " << from << " to " << to<<endl;
		process(N - 1, help, to, from);
	}
}
int main()
{
	int n = 3;//三层汉诺塔问题
	//hanoi(3);//
	process(n, "左","右","中");

	return 0;
}

