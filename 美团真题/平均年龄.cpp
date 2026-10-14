#include <iostream> // 使用处：第 8 行的 cin
#include <cmath> // 使用处：第 15 行的 ceil
using namespace std;
int main()
{
	int w, n;
	double x, y;
	while (cin >> w >> y >> x >> n) {	
		for (int i = 0; i < n; i++) {
			double leave = w * x;
			double rest = w - leave;
			double avg = (rest * (y+1.0) + leave * 21) / (double)w;
			y = avg;
		}
		cout << ceil(y) <<endl;
	}
	return 0;

}
