// 原理总结：归并排序先把区间递归拆成两半，再合并两个有序子区间。
// 合并时比较两边当前元素，将较小者放进临时数组，最后复制回原数组。
// 时间复杂度 O(n log n)，合并过程需要 O(n) 额外空间。
#include <iostream>
#include <vector>
using namespace std;
void mergesort(vector<int> &arr, int L, int R) {
  // 单个元素天然有序；调用方应保证输入区间非空且下标有效。
  if (L == R)
    return;
  int mid = L + (R - L) / 2;
  // 先分别排序左半段和右半段。
  mergesort(arr, L, mid);
  mergesort(arr, mid + 1, R);
  int i = 0;
  vector<int> help(R - L + 1);
  int p1 = L;
  int p2 = mid + 1;
  // 每次取两段中较小的当前值。
  while (p1 <= mid && p2 <= R) {
    help[i++] = arr[p1] < arr[p2] ? arr[p1++] : arr[p2++];
  }
  while (p1 <= mid) {
    // 右段已耗尽，直接复制左段剩余元素。
    help[i++] = arr[p1++];
  }
  while (p2 <= R) {
    // 左段已耗尽，直接复制右段剩余元素。
    help[i++] = arr[p2++];
  }
  // 把合并后的有序结果写回原区间。
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
