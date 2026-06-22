#include < unordered_map>
#include < unordered_set>
#include <algorithm> //包含堆操作
#include <assert.h>
#include <cmath>
#include <ctime>
#include <deque> //双端队列，兼顾随即存取，和两端数据的插入删除
#include <iostream>
#include <list> //类似双向链表，随即存取效率差，不支持[]符号，但是插入和删除效率高
#include <map>
#include <queue> //队列
#include <set>
#include <sstream> //istringstream 可以将string以空格为分隔符分割
#include <stack>   //栈
#include <string>
#include <vector> //不注重插入和删除效率

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