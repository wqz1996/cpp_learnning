#include <iostream> // 使用处：第 20 行的 cout
#include <vector> // 使用处：第 38 行的 vector
#include <deque> // 使用处：第 8 行的 deque
using namespace std;
class MeanFilter
{
private:
	deque<double> windows;
	int window_size;
	double sum;

public:
	MeanFilter(double _window_size) : window_size(_window_size), sum(0.0) {}
	double Filter(double x)
	{
		if (windows.size() < window_size)
		{
			windows.push_front(x);
			sum += x;
			cout << "sum: " << sum << endl;
		}
		else
		{
			sum -= windows.back();
			windows.pop_back();
			windows.push_front(x);
			sum += x;
			cout << "sum: " << sum << endl;
		}
		if (windows.empty())
			return 0.0;
		double output = sum / double(windows.size());
		return output;
	}
};
int main()
{
	vector<double> output;
	vector<double> input = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
	int window_size = 3;
	MeanFilter filter(window_size);
	cout << "input: " << endl;
	for (double &val : input)
	{
		cout << val << " ";
		output.push_back(filter.Filter(val));
	}
	cout << endl;
	cout << "output: " << endl;
	for (double &val : output)
	{
		cout << val << " ";
	}
	cout << endl;
	return 0;
}