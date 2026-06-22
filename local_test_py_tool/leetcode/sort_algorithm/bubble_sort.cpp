#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
void bubblesort(vector<double> &arr) {
  for (int i = 0; i < arr.size(); i++) {
    for (int j = i + 1; j < arr.size(); j++) {
      if (arr[j] < arr[i])
        swap(arr[j], arr[i]);
    }
  }
}

int main() {
  vector<double> arr = {2, 1, 3, 5, 4};
  cout << "before | " << endl;
  for (double &v : arr) {
    cout << v;
  }
  cout << endl;
  bubblesort(arr);
  cout << "after | " << endl;
  for (double &v : arr) {
    cout << v;
  }
  cout << endl;
  return 0;
}
