#include <algorithm> // 使用处：第 13 行的 swap(
#include <iostream> // 使用处：第 39 行的 cout
#include <vector> // 使用处：第 5 行的 vector
using namespace std;
vector<int> partition(vector<double> &arr, int L, int R)
{
	less = L - 1;
	more = R;
	while (L < more)
	{
		if (arr[L] < arr[R])
		{
			swap(arr[++less], arr[L++]);
		}
		else if (arr[L] > arr[R])
		{
			swap(arr[--more], arr[L])
		}
		else
		{
			L++;
		}
		swap(arr[more], arr[R]);
		return vector<int>{less + 1, R};
	}
}
void quicksort(vector<double> &arr, int L, int R)
{
	if (L >= R)
		return;
	vector<int> p = partition(arr, L, R);
	quicksort(arr, L, p[0] - 1);
	quicksort(arr, p[1] + 1, R);
}
int main()
{
	vector<int> arr{2, 5, 1, 3, 4};
	quicksort(arr, 0, arr.size());
	cout << "qize";
	return 0;
}
