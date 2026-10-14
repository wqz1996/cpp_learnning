#include <algorithm> // 使用处：第 12 行的 swap(
#include <iostream> // 使用处：第 18 行的 cout
#include <vector> // 使用处：第 5 行的 vector
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