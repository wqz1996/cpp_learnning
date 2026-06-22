#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
void insertsort(vector<double> &arr) {
  int i, j;
  for (i = 1; i < arr.size(); i++) {
    double key = arr[i];
    for (j = i - 1; j >= 0 && arr[j] > key; j--) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = key;
    // 打印每次迭代后的数组
    cout << endl;
    for (double val : arr) {
      cout << val << " ";
    }
    cout << endl;
  }
}

int main() {
  vector<double> arr = {4, 1, 5, 3, 2, 7, 6};
  cout << "before | " << endl;
  for (double &v : arr) {
    cout << v;
  }
  cout << endl;
  insertsort(arr);
  cout << "after | " << endl;
  for (double &v : arr) {
    cout << v;
  }
  cout << endl;
  return 0;
}
