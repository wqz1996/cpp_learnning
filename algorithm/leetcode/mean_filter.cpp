#include <algorithm> //包含堆操作
#include <iostream>
#include <sstream> //istringstream 可以将string以空格为分隔符分割
#include <string>
#include <cmath>
#include <stack>  //栈
#include <queue>  //队列
#include <vector> //不注重插入和删除效率
#include <list>	  //类似双向链表，随即存取效率差，不支持[]符号，但是插入和删除效率高
#include <deque>  //双端队列，兼顾随即存取，和两端数据的插入删除
#include <ctime>
#include <unordered_map>
#include <unordered_set>
#include <hash_map>
#include <hash_set>
#include <assert.h>
#include <set>
#include <map>
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