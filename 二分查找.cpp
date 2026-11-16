#include <iostream> // 使用处：第 60 行的 cout
#include <vector>   // 使用处：第 7 行的 vector

using namespace std;
class Solution {
public:
  int findnum(vector<int> nums,
              int target) { //查找target在arr中索引，没有则返回-1
    int len = nums.size();
    int left = 0;
    int right = len - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] == target)
        return mid;
      else if (nums[mid] < target)
        left = mid + 1;
      else if (nums[mid] > target)
        right = mid - 1;
    }
    return -1;
  }
  int left_bound(vector<int> nums, int target) { //左边界
    int len = nums.size();
    int left = 0;
    int right = len - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] == target)
        right = mid - 1;
      else if (nums[mid] < target)
        left = mid + 1;
      else if (nums[mid] > target)
        right = mid - 1;
    }
    // 如果指针越界，则说明数组中没有target
    if (left < 0 || left >= nums.size()) {
      return -1;
    }
    // 没越界也可能不存在target，如果数组中没有target，返回 -1
    if (nums[left] != target)
      return -1;
    return left;
  }
  int right_bound(vector<int> nums, int target) { //右边界
    int len = nums.size();
    int left = 0;
    int right = len - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] == target)
        left = mid + 1;
      else if (nums[mid] < target)
        left = mid + 1;
      else if (nums[mid] > target)
        right = mid - 1;
    }
    // 如果指针越界，则说明数组中没有target
    if (right < 0 || right >= nums.size()) {
      return -1;
    }
    // 如果数组中没有target，返回 -1
    if (nums[right] != target)
      return -1;
    return right;
  }
};
int main() {

  vector<int> nums = {1, 2, 2, 4};
  int right_bound_res = Solution().right_bound(nums, 2);
  cout << "right bound: " << right_bound_res << endl;
  int left_bound_res = Solution().left_bound(nums, 2);
  cout << "left bound: " << left_bound_res << endl;
  return 0;
}