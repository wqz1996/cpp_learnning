#include <iostream> // 使用处：第 60 行的 cout
#include <vector> // 使用处：第 7 行的 vector

using namespace std;
class Solution {
public:
  int findnum(vector<int> arr,
              int target) { //查找target在arr中索引，没有则返回-1
    int len = arr.size();
    int left = 0;
    int right = len - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (arr[mid] == target)
        return mid;
      else if (arr[mid] < target)
        left = mid + 1;
      else if (arr[mid] > target)
        right = mid - 1;
    }
    return -1;
  }
  int left_bound(vector<int> arr, int target) { //左边界
    int len = arr.size();
    int left = 0;
    int right = len - 1;
    while (left < right) {
      int mid = left + (right - left) / 2;
      if (arr[mid] == target)
        right = mid;
      else if (arr[mid] < target)
        left = mid + 1;
      else if (arr[mid] > target)
        right = mid - 1;
    }

    return arr[left] == target ? left : -1;
  }
  int right_bound(vector<int> arr, int target) { //右边界
    int len = arr.size();
    int left = 0;
    int right = len - 1;
    while (left < right) {
      int mid = left + (right - left) / 2;
      if (arr[mid] == target)
        left = mid + 1;
      else if (arr[mid] < target)
        left = mid + 1;
      else if (arr[mid] > target)
        right = mid - 1;
    }

    return arr[left - 1] == target ? left - 1 : -1;
  }
};
int main() {

  vector<int> arr = {1, 2, 2, 4};
  int res = Solution().right_bound(arr, 2);
  cout << res << endl;
  return 0;
}