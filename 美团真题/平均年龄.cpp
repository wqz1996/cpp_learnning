#include<iostream>
#include<cmath>
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
