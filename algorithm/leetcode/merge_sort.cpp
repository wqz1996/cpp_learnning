#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
void mergesort(vector<int> &arr, int L, int R) {
  if (L == R)
    return;
  int mid = L + (R - L) / 2;
  mergesort(arr, L, mid);
  mergesort(arr, mid + 1, R);
  int i = 0;
  vector<int> help(R - L + 1);
  int p1 = L;
  int p2 = mid + 1;
  while (p1 <= mid && p2 <= R) {
    help[i++] = arr[p1] < arr[p2] ? arr[p1++] : arr[p2++];
  }
  while (p1 <= mid) {
    help[i++] = arr[p1++];
  }
  while (p2 <= R) {
    help[i++] = arr[p2++];
  }
  for (i = 0; i < help.size(); i++) {
    arr[L + i] = help[i];
  }
}

int main() {
  vector<int> arr = {2, 1, 3, 5, 4};
  cout << "before | " << endl;
  for (int &v : arr) {
    cout << v;
  }
  cout << endl;
  mergesort(arr, 0, arr.size() - 1);
  cout << "after | " << endl;
  for (int &v : arr) {
    cout << v;
  }
  cout << endl;
  return 0;
}