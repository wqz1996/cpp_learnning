#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
void selectsort(vector<double> &arr) {
  int min;
  for (int i = 0; i < arr.size(); i++) {
    min = i;
    for (int j = i + 1; j < arr.size(); j++) {
      min = arr[j] < arr[min] ? j : min;
    }
    swap(arr[i], arr[min]);
  }
}

int main() {
  vector<double> arr = {2, 1, 3, 5, 4};
  cout << "before | " << endl;
  for (double &v : arr) {
    cout << v;
  }
  cout << endl;
  selectsort(arr);
  cout << "after | " << endl;
  for (double &v : arr) {
    cout << v;
  }
  cout << endl;
  return 0;
}