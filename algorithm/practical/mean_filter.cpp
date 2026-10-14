// 原理总结：滑动均值滤波只保留最近 window_size 个样本。
// 新样本进入时更新累计和；窗口已满则先移除最旧样本。
// 用累计和除以当前样本数得到均值，前几个样本按实际窗口长度计算。
// 调用时要求 window_size 为正数。
#include <iostream>
#include <vector>
#include <deque>
using namespace std;
class MeanFilter
{
private:
	deque<double> windows;
	int window_size;
	double sum; // 当前窗口内所有样本的和。

public:
	MeanFilter(double _window_size) : window_size(_window_size), sum(0.0) {}
	double Filter(double x)
	{
		// 窗口未满时直接加入；满时先减去最旧值，保持固定长度。
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
		// 启动阶段除以当前元素数，而不是固定的窗口大小。
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
