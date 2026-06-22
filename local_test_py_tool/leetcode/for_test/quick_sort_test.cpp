#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
vector<int> partition(vector<double> &arr, int L, int R) {
  int less = L - 1;
  int more = R;
  while (L < more) {
    if (arr[L] < arr[R]) {
      swap(arr[++less], arr[L++]);
    } else if (arr[L] > arr[R]) {
      swap(arr[--more], arr[L]);
    } else {
      L++;
    }
  }
  swap(arr[more], arr[R]);
  return vector<int>{less + 1, more};
}

void quicksort(vector<double> &arr, int L, int R) {
  if (L >= R)
    return;
  vector<int> p = partition(arr, L, R);
  quicksort(arr, L, p[0] - 1);
  quicksort(arr, p[1] + 1, R);
}
int main() {
  vector<double> arr = {2, 1, 3, 5, 4};
  cout << "before | " << endl;
  for (double &v : arr) {
    cout << v;
  }
  cout << endl;
  quicksort(arr, 0, arr.size() - 1);
  cout << "after | " << endl;
  for (double &v : arr) {
    cout << v;
  }
  cout << endl;
  return 0;
}
