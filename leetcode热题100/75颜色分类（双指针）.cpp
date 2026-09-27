#include <iostream> // cout, endl：第 56 行首次使用
#include <vector> // vector：第 10 行首次使用
#include <cassert> // assert：第 13 行首次使用
using namespace std;
/************75颜色分类*********************/
//给定有n个元素的数组，元素取值只有0，1，2三种可能
//给数组排序
class Solution {
public:
	void sortColors(vector<int>& nums) {
		int count[3] = { 0 };
		for (int i = 0; i < nums.size(); i++) {
			assert(nums[i] >= 0 && nums[i] <= 2);
			count[nums[i]]++;
		}
		int index = 0;
		for (int i = 0; i < (sizeof(count) / sizeof(int)); i++) {
			for (int j = 0; j < count[i]; j++) {
				nums[index++] = i;
			}
		}
		
	}
	void swap(vector<int>& nums, int i, int j) {
		int temp = nums[i];
		nums[i] = nums[j];
		nums[j] = temp;
	}
	void sortColors1(vector<int>& nums) {
		int zero = -1;
		int two = nums.size();
		int i = 0;
		while (i < two) {
			if (nums[i] == 1)
				i++;
			else if (nums[i] == 2) {
				swap(nums, i, --two);
			}
			else {
				assert(nums[i] == 0);
				swap(nums, ++zero, i++);
			}

		}

	}
};
int main()
{
    const vector<int> input{2, 0, 2, 1, 1, 0};
    vector<int> a = input, b = input;
    Solution solution;
    solution.sortColors(a);
    solution.sortColors1(b);
    for (const auto& result : {a, b}) {
        for (int value : result) cout << value << ' ';
        cout << endl;
    }
    return 0;
}
